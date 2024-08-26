/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:55:19 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 14:52:12 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_memchr = 0;

int	memchr_cmp(int test_count, char *test, int c, size_t n)
{
	FILE	*errorlog;
	char	*org;
	char	*ft;

	errorlog = fopen("logs/error_log.txt", "a");
	if (errorlog == NULL)
	{
		printf("Error opening log file\n");
		return (1);
	}
	org = memchr(test, c, n);
	ft = ft_memchr(test, c, n);
	if (org != ft)
		g_fail_memchr += ft_log_str(test_count, errorlog, org, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	fclose(errorlog);
	return (test_count + 1);
}

int	memchr_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = memchr_cmp(test_count, "fnjkdvbs", 'n', 5);
	test_count = memchr_cmp(test_count, "    scnaocuw9/", '/', 20);
	test_count = memchr_cmp(test_count, "fnjkdvbs", 'n', 0);
	test_count = memchr_cmp(test_count, "snsicnsk sjknsjanc", ' ', 10);
	test_count = memchr_cmp(test_count, "fnjkdvbs\n", '\200', 1000);
	test_count = memchr_cmp(test_count, "fnjkdvbs\n", '\n', 16);
	test_count = memchr_cmp(test_count, "fnjkdvb0", '\0', 20);
	return (g_fail_memchr);
}
