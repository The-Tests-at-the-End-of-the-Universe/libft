/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:55:19 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 09:05:24 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fail_memchr = 0;

typedef struct s_memchr_test
{
	char	*test;
	int		c;
	size_t	n;
}	t_memchr_test;

static const t_memchr_test	g_tests[] = {
[0] = {"fnjkdvbs", 'n', 5},
[1] = {"    scnaocuw9/", '/', 15},
[2] = {"fnjkdvbs", 'n', 0},
[3] = {"snsicnsk sjknsjanc", ' ', 10},
[4] = {"fnjkdvbs\n", '\200', 9},
[5] = {"fnjkdvbs\n", '\n', 9},
[6] = {"fnjkdvb0", '\0', 9},
[7] = {"ab", 'a', 2},
[8] = {"ab", 'b', 2},
[9] = {"a", 'a', 1},
[10] = {"a", 'b', 1},
[11] = {"bbbbaaaa", 'a', 8},
[12] = {"bbbbaaaa", 'b', 8},
[13] = {"aaaaaaab", 354, 8},
[14] = {"aaaaaaab", 'b', 1},
[15] = {"aaaaaaab", 'b', 8},
};

static const t_memchr_test	g_ftests[] = {
[0] = {"", 0, 0},
[1] = {NULL, 354, 8},
[2] = {"a", 'b', 100},
};

void	memchr_fork(int test_count, pid_t *child, void **shmem, \
void *(*f)(const void *, int c, size_t n))
{
	char	*ret;
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = strdup(g_tests[test_count].test);
		f(ret, g_tests[test_count].c, g_tests[test_count].n);
		memmove(*shmem, ret, strlen(ret));
		exit(0);
	}
}
int	memchr_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];
	char	*mem_test;

	memchr_fork(test_count, &childs[0], org_shmem, &memchr);
	memchr_fork(test_count, &childs[1], ft_shmem, &ft_memchr);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = strdup(g_tests[test_count].test); 
	ft_memchr(mem_test, g_tests[test_count].c, g_tests[test_count].n);
	free(mem_test);
	if (chrcmp((char*)*org_shmem, (char*)*ft_shmem, g_tests[test_count].n))
	{
		g_fail_memchr += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %d [n] %ld\n", g_tests[test_count].test, \
		g_tests[test_count].c, g_tests[test_count].n);
	}
	return (0);
}

int	memchr_test(int test_count, char* fail_flag)
{
	void	*org_shmem;
	void	*ft_shmem;

	if (fail_flag)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (!strcmp("-ft", fail_flag))
			org_shmem= ft_memchr(g_ftests[test_count].test, g_ftests[test_count].c, g_ftests[test_count].n);
		if (!strcmp("-og", fail_flag))
			org_shmem = memchr(g_ftests[test_count].test, g_ftests[test_count].c, g_ftests[test_count].n); 
		return (g_fail_memchr);
	}
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	memchr_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_memchr);
}
