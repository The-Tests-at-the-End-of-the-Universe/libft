/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_istotester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:29:29 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/13 15:48:46 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <ctype.h>

int					g_fail_isto = 0;

static const char	g_tests[] = {
[ZERO] = 'a',
[ONE] = 'A',
[TWO] = 'z',
[THREE] = '\n',
[FOUR] = '\200',
[FIVE] = '\100',
[SIX] = (char)359,
[SEVEN] = 255,
[EIGHT] = '"',
[NINE] = ' ',
[TEN] = (char)1243,
};


void	isto_fork(int test_count, pid_t *child, int (*f)(int))
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		f(g_tests[test_count]);
		exit(0);
	}
}

int	isto_cmp(int test_count, int (*func)(int), int (*ft_func)(int))
{
	pid_t	childs[2];
	int		ft;
	int		org;

	isto_fork(test_count, &childs[0], func);
	isto_fork(test_count, &childs[1], ft_func);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	ft = ft_func(g_tests[test_count]);
	org = func(g_tests[test_count]);
	if ((ft && org) || (!ft && !org));
	else
	{
		printf("ft: %d org: %d\n", ft, org);
		g_fail_isto += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %d\n", g_tests[test_count]);
	}
	return (0);
}

int	isto_test(int test_count, int (*f)(int), int (*ft)(int), char *fail_flag)
{
	if (fail_flag != NULL)
		return (FINISH);
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	isto_cmp(test_count, f, ft);
	return (g_fail_isto);
}
