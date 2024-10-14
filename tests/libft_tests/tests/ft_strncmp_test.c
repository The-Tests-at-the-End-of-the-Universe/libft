/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 09:03:20 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fail_strncmp = 0;

typedef struct s_strncmp_test
{
	char	*test;
	char	*test2;
	int		n;
}	t_strncmp_test;

static t_strncmp_test	g_tests[] = {
[0] = {"", "", 0}, 
[1] = {"bobobbocob", "dlksadbs", 5},
[2] = {"a", "b", 2},
[3] = {"dfsfdsf?", "??cbdscds", 6},
[4] = {"", "", 0},
[5] = {" ", " ", 2},
};

void	strncmp_fork(int test_count, pid_t *child, \
int (*f)(const char *, const char *, size_t))
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		f(g_tests[test_count].test, g_tests[test_count].test2, g_tests[test_count].n);
		exit(0);
	}
}
//added multiple conditions because returns value of strncmp can differ
//per compiler
//https://stackoverflow.com/questions/52334056/weird-return-value-in-strcmp
int	strncmp_cmp(int test_count)
{
	pid_t	childs[2];
	int		ft;
	int		org;

	strncmp_fork(test_count, &childs[0], &strncmp);
	strncmp_fork(test_count, &childs[1], &ft_strncmp);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	ft = ft_strncmp(g_tests[test_count].test, g_tests[test_count].test2, g_tests[test_count].n);
	org = strncmp(g_tests[test_count].test, g_tests[test_count].test2, g_tests[test_count].n);
	if((ft < 0 && org < 0) || (ft == 0 && org == 0) || (ft > 0 && org > 0));
	else
	{
		g_fail_strncmp += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %s\n", g_tests[test_count].test);
	}
	return (0);
}

int	strncmp_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	strncmp_cmp(test_count);
	return (g_fail_strncmp);
}
