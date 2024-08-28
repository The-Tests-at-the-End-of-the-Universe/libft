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

int	g_fail_memcmp = 0;

int	memcmp_cmp(int test_count, char *test, char *test2, size_t n)
{
	int		org;
	int		ft;

	org = memcmp(test, test2, n);
	ft = ft_memcmp(test, test2, n);
	if (org != ft)
	{
		g_fail_memcmp += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %s [2] %s\n", test, test2);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	memcmp_test(void)
{
	int	tc;

	tc = 1;
	tc = memcmp_cmp(tc, "fnjkdvbs", "fnjkdvbs", 5);
	tc = memcmp_cmp(tc, "    scnaocuw9/", "    scnaocuw9/", 20);
	tc = memcmp_cmp(tc, "fnjkdvbs", "fnjkdvss", 20);
	tc = memcmp_cmp(tc, "snsicnsk sjknsjanc", "snsicnsk sjknsjanc", 10);
	tc = memcmp_cmp(tc, "fnjkdvbs\n", "fnjkdvbs\n", 1000);
	tc = memcmp_cmp(tc, "fnjkdvbs\n", "fnjkdvbs\n", 16);
	tc = memcmp_cmp(tc, "fnjkdvb0", "fnjkdvb0", 20);
	tc = memcmp_cmp(tc, "NULL", "NULL", 0);
	return (g_fail_memcmp);
}
