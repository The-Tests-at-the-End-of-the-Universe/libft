/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 12:48:45 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/06 15:21:31 by mynodeus      ########   odam.nl         */
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
[ZERO] = {"", 0},
[ONE] = {"1", 1},
[TWO] = {"1", 1},
[THREE] = {"12", 1},
[FOUR] = {"123", 2},
[FIVE] = {"1234", 2},
[SIX] = {"  12345", 5},
[SEVEN] = {"123 456", 5},
[EIGHT] = {"A2143244535", 7},
[NINE] = {"2143244535", 7},
[TEN] = {" ", 1},
[ELEVEN] = {"asbj", 4},
[TWELVE] = {"       ", 1},
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

int	chrcmp(char *org, char *ft, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (org[i] != ft[i])
			return (1);
		i++;
	}
	return (0);
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

int	bzero_test(int test_count)
{
	void	*org_shmem;
	void	*ft_shmem;

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
