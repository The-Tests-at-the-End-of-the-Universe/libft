/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:55:19 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:56 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fail_memchr = 0;

typedef struct s_memchr_test
{
	char	*test;
	int		c;
	size_t	n;
}	t_memchr_test;

static const t_memchr_test	g_tests[] = {
[ZERO] = {"fnjkdvbs", 'n', 5},
[ONE] = {"    scnaocuw9/", '/', 20},
[TWO] = {"fnjkdvbs", 'n', 0},
[THREE] = {"snsicnsk sjknsjanc", ' ', 10},
[FOUR] = {"fnjkdvbs\n", '\200', 1000},
[FIVE] = {"fnjkdvbs\n", '\n', 16},
[SIX] = {"fnjkdvb0", '\0', 20},
};

int	memchr_cmp(int test_count)
{
	char	*org;
	char	*ft;

	org = memchr(g_tests[test_count].test, g_tests[test_count].c, \
	g_tests[test_count].n);
	ft = ft_memchr(g_tests[test_count].test, g_tests[test_count].c, \
	g_tests[test_count].n);
	if (org != ft)
	{
		g_fail_memchr += ft_log_str(test_count, org, ft);
		dprintf(2, "tcase: %s\n", g_tests[test_count].test);
		g_fail_memchr = 1;
	}
	else
		g_fail_memchr = 0;
	return (test_count + 1);
}

int	memchr_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	memchr_cmp(test_count);
	return (g_fail_memchr);
}
