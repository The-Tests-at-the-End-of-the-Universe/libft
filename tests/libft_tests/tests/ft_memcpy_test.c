/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:07:08 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:55 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_memcpy = 0;

typedef struct s_memcpy_test
{
	char	*test;
	char	*test2;
	int		n;
}	t_memcpy_test;

static t_memcpy_test	g_tests[] = {
[ZERO] = {"fnjkdvbs", "fnjkdvbs", 5},
[ONE] = {"    scnaocuw9/", "    scnaocuw9/", 20},
[TWO] = {"fnjkdvbs", "fnjkdvss", 20},
[THREE] = {"snsicnsk sjknsjanc", "snsicnsk sjknsjanc", 10},
[FOUR] = {"fnjkdvbs\n", "fnjkdvbs\n", 1000},
[FIVE] = {"fnjkdvbs\n", "fnjkdvbs\n", 16},
[SIX] = {"fnjkdvb0", "fnjkdvb0", 20},
[SEVEN] = {"NULL", "NULL", 0},
};

char	*init_ft(char *test, char *test2, size_t n)
{
	char	*test_dub;
	char	*test2_dub;
	char	*ret;

	test_dub = strdup(test);
	test2_dub = strdup(test2);
	if (test_dub == NULL || test2_dub == NULL)
	{
		if (test_dub)
			free(test_dub);
		if (test2_dub)
			free(test2_dub);
		printf("Error with initft\n");
		return (NULL);
	}
	ret = ft_memcpy(test_dub, test2_dub, n);
	free(test2_dub);
	return (ret);
}

char	*init_org(char *test, char *test2, size_t n)
{
	char	*test_dub;
	char	*test2_dub;
	char	*ret;

	test_dub = strdup(test);
	test2_dub = strdup(test2);
	if (test_dub == NULL || test2_dub == NULL)
	{
		if (test_dub)
			free(test_dub);
		if (test2_dub)
			free(test2_dub);
		printf("Error with init_org\n");
		return (NULL);
	}
	ret = memcpy(test_dub, test2_dub, n);
	free(test2_dub);
	return (ret);
}

void	memcpy_fork(int test_count, pid_t *child, void **shmem)
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		*shmem = init_org(g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
		exit(0);
	}
}

int	memcpy_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];

	memcpy_fork(test_count, &childs[0], org_shmem);
	memcpy_fork(test_count, &childs[1], ft_shmem);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " MKO "RESET));
	if (strcmp(*org_shmem, *ft_shmem))
	{
		g_fail_memcpy += ft_log_str(test_count, *org_shmem, *ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %s [n] %d\n", g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
	}
	return (0);
}

//shared memory: 
// https://stackoverflow.com/questions/5656530/
// how-to-use-shared-memory-with-linux-in-c
int	memcpy_test(int test_count)
{
	void	*org_shmem;
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	memcpy_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_memcpy);
}
