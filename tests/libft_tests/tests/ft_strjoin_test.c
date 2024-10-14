/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:57:44 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 09:03:31 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_strjoin = 0;

typedef struct s_strjoin_test
{
	char	*s1;
	char	*s2;
	char	*result;
}	t_strjoin_test;

static t_strjoin_test	g_tests[] = {
[0] = {"", "", ""},
[1] = {"nfdsnkjd", "dlksadbs", "nfdsnkjddlksadbs"},
[2] = {"bobobbocob", "dlksadbs", "bobobbocobdlksadbs"},
[3] = {"a", "b", "ab"},
[4] = {"dfsfdsf?", "??cbdscds", "dfsfdsf???cbdscds"},
[5] = {"", "", ""},
[6] = {" ", " ", "  "},
};

void	strjoin_fork(int test_count, pid_t *child, void **shmem, \
char *(*f)(const char *, const char *))
{
	char *res;

	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		res = f(g_tests[test_count].s1, g_tests[test_count].s2);
		memmove(*shmem, res, strlen(res));
		exit(0);
	}
}

int	strjoin_cmp(int test_count, void **ft_shmem)
{
	pid_t	childs[1];
	char	*test;

	strjoin_fork(test_count, &childs[0], ft_shmem, &ft_strjoin);
	if (wait_child(childs[0]))
		return (printf(RED " SEGFAULT  "RESET));
	test = ft_strjoin(g_tests[test_count].s1, g_tests[test_count].s2);
	free(test);
	if (strcmp(g_tests[test_count].result, (char*)*ft_shmem))
	{
		g_fail_strjoin += ft_log_str(test_count, g_tests[test_count].result, (char*)*ft_shmem);
		dprintf(2, "tcase: [s1] %s [s2] %s [result] %s\n", g_tests[test_count].s1, \
		g_tests[test_count].s2, g_tests[test_count].result);
		g_fail_strjoin = 1;
	}
	return (0);
}

int	strjoin_test(int test_count)
{
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].result));
	if (strjoin_cmp(test_count, &ft_shmem))
		g_fail_strjoin = 1;
	if (munmap(ft_shmem, sizeof(g_tests[test_count].result)))
		exit(1);
	return (g_fail_strjoin);
}
