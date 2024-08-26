/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_istotester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:29:29 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 15:52:10 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <ctype.h>

int	g_fail_isto = 0;

int	isto_cmp(int tc, int c, int (*f)(int), int (*ft)(int))
{
	int		org_func;
	int		ft_func;

	org_func = f(c);
	ft_func = ft(c);
	if (org_func != ft_func)
		g_fail_isto += ft_log_int(tc, org_func, ft_func);
	else
		printf(GRN "%d OK " RESET, tc);
	return (tc + 1);
}

int	isto_test(char *function_name, int (*f)(int), int (*ft)(int))
{
	int	test_count;

	test_count = 1;
	(void)function_name;
	test_count = isto_cmp(test_count, 'a', f, ft);
	test_count = isto_cmp(test_count, 'A', f, ft);
	test_count = isto_cmp(test_count, 'z', f, ft);
	test_count = isto_cmp(test_count, '\n', f, ft);
	test_count = isto_cmp(test_count, '\200', f, ft);
	test_count = isto_cmp(test_count, '\100', f, ft);
	test_count = isto_cmp(test_count, 359, f, ft);
	test_count = isto_cmp(test_count, 255, f, ft);
	test_count = isto_cmp(test_count, '"', f, ft);
	test_count = isto_cmp(test_count, ' ', f, ft);
	test_count = isto_cmp(test_count, 1243, f, ft);
	return (g_fail_isto);
}
