/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 10:29:37 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int	g_fail_strlen = 0;

typedef struct s_strlen_test
{
	char	*test;
}	t_strlen_test;

static const t_strlen_test	g_tests[] = {
[0] = {""},
[1] = {"bobobbocob"},
[2] = {"a"},
[3] = {""},
[4] = {" "},
[5] = {"nfdsnkjd"},
};

static t_strlen_test	g_ftests[] = {
[0] = {""}, 
[1] = {NULL},
};


void	strlen_fork(int test_count, pid_t *child, \
size_t (*f)(const char *))
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		f(g_tests[test_count].test);
		exit(0);
	}
}
int	strlen_cmp(int test_count)
{
	pid_t	childs[2];
	int		ft;
	int		org;

	strlen_fork(test_count, &childs[0], &strlen);
	strlen_fork(test_count, &childs[1], &ft_strlen);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	ft = ft_strlen(g_tests[test_count].test);
	org = strlen(g_tests[test_count].test);
	if (ft != org)
	{
		g_fail_strlen += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %s\n", g_tests[test_count].test);
	}
	return (0);
}

int	strlen_test(int test_count, char *fail_flag)
{
	size_t test;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	if (fail_flag)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (!strcmp("-ft", fail_flag))
			test = ft_strlen(g_ftests[test_count].test);
		if (!strcmp("-og", fail_flag))
			test = strlen(g_ftests[test_count].test);
		(void)test;
		return (g_fail_strlen);
	}
	strlen_cmp(test_count);
	return (g_fail_strlen);
}
