/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_istotester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:29:29 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:58 by spenning      ########   odam.nl         */
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

int	isto_cmp(int tc, int (*f)(int), int (*ft)(int))
{
	int		org_func;
	int		ft_func;

	org_func = f(g_tests[tc]);
	ft_func = ft(g_tests[tc]);
	if (org_func == 0 && ft_func != 0)
	{
		g_fail_isto += ft_log_int(tc, org_func, ft_func);
		dprintf(2, "tcase: %d\n", g_tests[tc]);
		g_fail_isto = 1;
	}
	else
		g_fail_isto = 0;
	return (g_fail_isto);
}

int	isto_test(int test_count, char *function_name, \
int (*f)(int), int (*ft)(int))
{
	(void)function_name;
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	isto_cmp(test_count, f, ft);
	return (g_fail_isto);
}
