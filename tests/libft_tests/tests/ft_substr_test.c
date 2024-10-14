/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:51:07 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 17:55:11 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_substr = 0;

typedef struct s_substr_test
{
	char	*test;
	char	*result;
	unsigned int		start;
	size_t		len;
}	t_substr_test;

static t_substr_test	g_tests[] = {
[0] = {"", "", 0, 0},
[1] = {"nfdsnkjdsnciudsbccknd?cbdscds", "kjdsnciu", 5, 8},
[2] = {"bobobbocobedbobobbobob!", "bobobbocobedbobobbobob!", 0, 23},
[3] = {"dfsfdsf???cbdscds", "sfdsf???cbdscd", 2, 14},
[4] = {"aaaaaaaa", "\0", -1, 2},
[5] = {"aaaaaaaa", "aaaaaa", 2, 10},
[6] = {"aaaaaaaa", "\0", 2, 0},
[7] = {"aaaaaaaa", "aaaaaaa", 1, -2},
[8] = {"aaaaaaaa", "aaa", 0, 3},
[9] = {"he\nllo\tworld", "\nllo\t", 2, 5},
};

static t_substr_test	g_ftests[] = {
[0] = {NULL, NULL, 0, 0},
[1] = {NULL, NULL, 1, 2},
[2] = {NULL, NULL, 0, 0},
};

void	substr_fork(int test_count, pid_t *child, void **shmem, \
char *(*f)(const char *dst, unsigned int start, size_t))
{
	char	*ret;
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = f(g_tests[test_count].test, g_tests[test_count].start, g_tests[test_count].len);
		memmove(*shmem, ret, strlen(ret));
		exit(0);
	}
}

int	substr_cmp(int test_count, void **ft_shmem)
{
	pid_t	childs[1];
	char	*mem_test;

	substr_fork(test_count, &childs[0], ft_shmem, &ft_substr);
	if (wait_child(childs[0]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = ft_substr(g_tests[test_count].test, g_tests[test_count].start, g_tests[test_count].len);
	free(mem_test);
	if (strcmp(g_tests[test_count].result, (char*)*ft_shmem))
	{
		g_fail_substr += ft_log_str(test_count, g_tests[test_count].result, (char*)*ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %d [3] %ld\n", g_tests[test_count].test, \
		g_tests[test_count].start, g_tests[test_count].len);
	}
	return (0);
}

int	substr_test(int test_count, char *fail_flag)
{
	void	*ft_shmem;

	if (fail_flag)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);
		if (!strcmp("-ft", fail_flag))
			ft_shmem = ft_substr(g_ftests[test_count].test, g_ftests[test_count].start, g_ftests[test_count].len);
		if (!strcmp("-og", fail_flag))
			return (0);
		free(ft_shmem);
		return (g_fail_substr);
	}
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	substr_cmp(test_count, &ft_shmem);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_substr);
}
