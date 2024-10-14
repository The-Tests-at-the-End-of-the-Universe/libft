/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:26:06 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 09:12:12 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_memset = 0;

typedef struct s_memset_test
{
	char	*test;
	int		test2;
	int		n;
}	t_memset_test;

static t_memset_test	g_tests[] = {
[0] = {"fnjkdvbs", 'c', 2},
[1] = {"    scnaocuw9/", 'a', 10},
[2] = {"fnjkdvbs", '\n', 4},
[3] = {"snsicnsk sjknsjanc", 0, 10},
[4] = {"fnjkdvbs\n", 255, 0},
[5] = {"fnjkdvbs\n", 's', 2},
[6] = {"fnjkdvb0", 's', 6},
[7] = {"NULL", 0, 0},
};

static const t_memset_test	g_ftests[] = {
[0] = {"", '0', 0},
[1] = {NULL, '0', 1},
[2] = {NULL, '0', 0},
[3] = {"NULL", 1, 4},
[4] = {"NULL", 300, 4},
[5] = {"NULL", 'a', 400},
[6] = {"NULL", -1, 4},
};

char	*init_ft_memset(char *test, int c, size_t n)
{
	char	*test_dub;

	test_dub = strdup(test);
	if (test_dub == NULL)
		return (NULL);
	return (ft_memset(test_dub, c, n));
}

char	*init_org_memset(char *test, int c, size_t n)
{
	char	*test_dub;

	test_dub = strdup(test);
	if (test_dub == NULL)
		return (NULL);
	return (memset(test_dub, c, n));
}

void	memset_fork(int test_count, pid_t *child, void **shmem, \
char *(*f)(char *, int, size_t n))
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		*shmem = f(g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
		exit(0);
	}
}

int	memset_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];
	void	*mem_test;

	memset_fork(test_count, &childs[0], org_shmem, &init_org_memset);
	memset_fork(test_count, &childs[1], ft_shmem, &init_ft_memset);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = strdup(g_tests[test_count].test); 
	ft_memset(mem_test, \
	g_tests[test_count].test2, g_tests[test_count].n);
	free(mem_test);
	if (strcmp((char*)*org_shmem, (char*)*ft_shmem))
	{
		g_fail_memset += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %d [n] %d\n", g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
	}
	return (0);
}

int	memset_test(int test_count, char *fail_flag)
{
	void	*org_shmem;
	void	*ft_shmem;
	if (fail_flag)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (!strcmp("-ft", fail_flag))
			(void)ft_memset(g_ftests[test_count].test, g_ftests[test_count].test2, g_ftests[test_count].n);
		if (!strcmp("-og", fail_flag))
			(void)memset(g_ftests[test_count].test, g_ftests[test_count].test2, g_ftests[test_count].n); 
		return (g_fail_memset);
	}
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	if (memset_cmp(test_count, &org_shmem, &ft_shmem))
		g_fail_memset = 1;
	if (munmap(org_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_memset);
}
