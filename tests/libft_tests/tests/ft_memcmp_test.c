/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:01:27 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:56 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fail_memcmp = 0;

typedef struct s_memcmp_test
{
	char	*test;
	char	*test2;
	int		n;
}	t_memcmp_test;

static const t_memcmp_test	g_tests[] = {
[ZERO] = {"fnjkdvbs", "fnjkdvbs", 5},
[ONE] = {"    scnaocuw9/", "    scnaocuw9/", 20},
[TWO] = {"fnjkdvbs", "fnjkdvss", 20},
[THREE] = {"snsicnsk sjknsjanc", "snsicnsk sjknsjanc", 10},
[FOUR] = {"fnjkdvbs\n", "fnjkdvbs\n", 1000},
[FIVE] = {"fnjkdvbs\n", "fnjkdvbs\n", 16},
[SIX] = {"fnjkdvb0", "fnjkdvb0", 20},
[SEVEN] = {"NULL", "NULL", 0},
};

int	memcmp_cmp(int test_count)
{
	int		org;
	int		ft;

	org = memcmp(g_tests[test_count].test, \
	g_tests[test_count].test2, g_tests[test_count].n);
	ft = ft_memcmp(g_tests[test_count].test, \
	g_tests[test_count].test2, g_tests[test_count].n);
	if (org != ft)
	{
		g_fail_memcmp += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %s [2] %s\n", g_tests[test_count].test, \
		g_tests[test_count].test2);
		g_fail_memcmp = 1;
	}
	else
		g_fail_memcmp = 0;
	return (test_count + 1);
}

int	memcmp_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	memcmp_cmp(test_count);
	return (g_fail_memcmp);
}
