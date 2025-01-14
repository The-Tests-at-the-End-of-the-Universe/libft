/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 10:39:26 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <bsd/string.h>

int	g_fail_strnstr = 0;

typedef struct s_strnstr_test
{
	char	*test;
	char	*test2;
	int		n;
}	t_strnstr_test;

static t_strnstr_test	g_tests[] = {
[0] = {"", "", 0}, 
[1] = {"bobobbocob", "dlksadbs", 5},
[2] = {"a", "b", 2},
[3] = {"dfsfdsf?", "??cbdscds", 6},
[4] = {"", "", 0},
[5] = {" ", " ", 2},
[6] = {"aaaaaa", "bbbbb", 0},
[7] = {"aaaaaa", "", 5},
[8] = {"aaaaaaaaaa", "bbbbbb", 3},
[9] = {"", "abbbbbb", 5},
};

static t_strnstr_test	g_ftests[] = {
[0] = {"", "", 0}, 
[1] = {"aaaaaa", NULL, 5},
[2] = {NULL, "bbbbbb", 5},
[3] = {"a", "bbbbbb", 5},
[4] = {"aaaaaaa", "abbbbbb", 100},
[5] = {"aaaaaaa", "abbbbbb", -100},
};

void	strnstr_fork(int test_count, pid_t *child, void **shmem, \
char * (*f)(const char *dst, const char *src, size_t n))
{
	char	*ret;
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = strdup(g_tests[test_count].test);
		f(ret, g_tests[test_count].test2, g_tests[test_count].n);
		memmove(*shmem, ret, strlen(ret));
		exit(0);
	}
}

int	strnstr_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];
	char	*mem_test;

	strnstr_fork(test_count, &childs[0], org_shmem, &strnstr);
	strnstr_fork(test_count, &childs[1], ft_shmem, &ft_strnstr);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = ft_strnstr(g_tests[test_count].test, g_tests[test_count].test2, g_tests[test_count].n);
	(void)mem_test;
	if (strcmp((char*)*org_shmem, (char*)*ft_shmem))
	{
		g_fail_strnstr += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %s [n] %d\n", g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
	}
	return (0);
}

int	strnstr_test(int test_count, char *fail_flag)
{
	void	*org_shmem;
	void	*ft_shmem;

	if (test_count == 9)
		g_tests[test_count].test = g_tests[test_count].test2 + 1; 
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	if (fail_flag)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (!strcmp("-ft", fail_flag))
			org_shmem = ft_strnstr(g_ftests[test_count].test, g_ftests[test_count].test2, g_ftests[test_count].n);
		if (!strcmp("-og", fail_flag))
			org_shmem = strnstr(g_ftests[test_count].test, g_ftests[test_count].test2, g_ftests[test_count].n);
		(void)org_shmem;
		return (g_fail_strnstr);
	}
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	strnstr_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_strnstr);
}
