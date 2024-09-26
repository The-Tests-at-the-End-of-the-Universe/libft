/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:26:06 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:54 by spenning      ########   odam.nl         */
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
[ZERO] = {"fnjkdvbs", 'c', 2},
[ONE] = {"    scnaocuw9/", 'a', 10},
[TWO] = {"fnjkdvbs", '\n', 4},
[THREE] = {"snsicnsk sjknsjanc", 0, 10},
[FOUR] = {"fnjkdvbs\n", 255, 0},
[FIVE] = {"fnjkdvbs\n", 's', 2},
[SIX] = {"fnjkdvb0", 's', 6},
[SEVEN] = {"NULL", 0, 0},
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

	memset_fork(test_count, &childs[0], org_shmem, &init_org_memset);
	memset_fork(test_count, &childs[1], ft_shmem, &init_ft_memset);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " MKO "RESET));
	if (strcmp(*org_shmem, *ft_shmem))
	{
		g_fail_memset += ft_log_str(test_count, *org_shmem, *ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %d [n] %d\n", g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
	}
	return (0);
}

int	memset_test(int test_count)
{
	void	*org_shmem;
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	memset_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_memset);
}
