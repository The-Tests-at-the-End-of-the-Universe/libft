/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:28:06 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 09:03:07 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_split = 0;

typedef struct s_split_test
{
	char	*string;
	char	*delim;
}	t_split_test;

static t_split_test	g_tests[] = {
[0] = {"", ""},
[1] = {"aaa;bbb,", ";"},
[2] = {"kokokokokokokoko", "o"},
[3] = {"hdkjsahdkjsa|hdkjsahdkjsa", "|"},
[4] = {"aaaa////aaaa//aa///", "/"},
};

int	cmp_split(char **ft_result, char *test, char *delim)
{
	int		index;
	char	*testret;
	char	*rest;
	char	*begin;

	index = 0;
	rest = strdup(test);
	begin = rest;
	while (ft_result[index] != NULL)
	{
		testret = __strtok_r(rest, delim, &rest);
		if (strcmp(testret, ft_result[index]))
		{
			free(begin);
			return (1);
		}
		index++;
	}
	free(begin);
	return (0);
}



void	split_fork(int test_count, pid_t *child, void **ft_shmem, \
char **(*f)(const char *, char))
{
	char **ft_result;

	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ft_result = f(g_tests[test_count].string, \
		g_tests[test_count].delim[0]);
		if (ft_result == NULL)
			exit(1);
		if (!cmp_split(ft_result, g_tests[test_count].string, \
		g_tests[test_count].delim))
			*(int*)*ft_shmem = 0;
		exit(0);
	}
}

int	split_cmp(int test_count, void **ft_shmem)
{
	pid_t	childs[1];
	char	**mem_test;

	split_fork(test_count, &childs[0], ft_shmem, &ft_split);
	if (wait_child(childs[0]))
		return (printf(RED " SEGFAULT  "RESET));
	mem_test = ft_split(g_tests[test_count].string, g_tests[test_count].delim[0]);
	for (int i = 0; mem_test[i] != NULL; i++)
		free(mem_test[i]);
	free(mem_test);
	g_fail_split = *(int*)*ft_shmem;
	if (g_fail_split)
	{
		ft_log_str(test_count, "Cannot show comparison", *ft_shmem);
		dprintf(2, "tcase: [string] %s [delim] %s\n", g_tests[test_count].string, \
		g_tests[test_count].delim);
	}
	return (0);
}

//shared memory: 
// https://stackoverflow.com/questions/5656530/
// how-to-use-shared-memory-with-linux-in-c
int	split_test(int test_count)
{
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	ft_shmem = create_shared_memory(sizeof(int));
	*(int*)ft_shmem = 1;
	if (split_cmp(test_count, &ft_shmem))
		g_fail_split = 1;
	if (munmap(ft_shmem, sizeof(int)))
		exit(1);
	return (g_fail_split);
}
