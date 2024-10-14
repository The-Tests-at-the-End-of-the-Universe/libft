/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 12:48:45 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 09:05:06 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fail_bzero = 0;

typedef struct s_bzero_test
{
	char	*string;
	int		num;
}	t_bzero_test;

static const t_bzero_test	g_tests[] = {
[0] = {"", 0},
[1] = {"1", 1},
[2] = {"1", 1},
[3] = {"12", 1},
[4] = {"123", 2},
[5] = {"1234", 2},
[6] = {"  12345", 5},
[7] = {"123 456", 5},
[8] = {"A2143244535", 7},
[9] = {"2143244535", 7},
[10] = {" ", 1},
[11] = {"asbj", 4},
[12] = {"       ", 1},
[13] = {"aaaaaaa", 0},
};

static const t_bzero_test	g_ftests[] = {
[0] = {"", 0},
[1] = {"aaaaaaa", -1},
[2] = {NULL, 1},
[3] = {"aaaaaaa", 20},
};

void	bzero_fork(int test_count, pid_t *child, void **shmem, \
void (*f)(void *, size_t n))
{
	char	*ret;

	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = strdup(g_tests[test_count].string);
		f(ret, g_tests[test_count].num);
		memcpy(*shmem, ret, strlen(g_tests[test_count].string));
		exit(0);
	}
}

int	bzero_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];
	char	*mem_test;

	bzero_fork(test_count, &childs[0], org_shmem, &bzero);
	bzero_fork(test_count, &childs[1], ft_shmem, &ft_bzero);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = strdup(g_tests[test_count].string);
	ft_bzero(mem_test, g_tests[test_count].num);
	free(mem_test);
	if (chrcmp((char*)*org_shmem, (char*)*ft_shmem, strlen(g_tests[test_count].string)))
	{
		g_fail_bzero += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %d\n", g_tests[test_count].string, \
		g_tests[test_count].num);
	}
	return (0);
}

int	bzero_test(int test_count, char *fail_flag)
{
	void	*org_shmem;
	void	*ft_shmem;
	
	if (fail_flag != NULL)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (!strcmp("-ft", fail_flag))
			(void)ft_bzero(g_ftests[test_count].string, g_ftests[test_count].num); 
		if (!strcmp("-og", fail_flag))
			(void)bzero(g_ftests[test_count].string, g_ftests[test_count].num); 
		return (g_fail_bzero);
	}
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	bzero_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	return (g_fail_bzero);
}
