/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:47:38 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 14:52:07 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <limits.h>

int	g_fail_itoa = 0;

int	itoa_cmp(int test_count, int test, char *test_case)
{
	FILE	*errorlog;
	char	*result_org;
	char	*result_ft;

	errorlog = fopen("logs/error_log.txt", "a");
	result_org = test_case;
	result_ft = ft_itoa(test);
	if (result_ft == NULL || errorlog == NULL)
	{
		printf("error with result_ft or errorlog\n");
		return (1);
	}
	if (strcmp(result_org, result_ft))
	{
		fprintf(errorlog, "ft_itoa\n");
		g_fail_itoa += ft_log_str(test_count, errorlog, result_org, result_ft);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	fclose(errorlog);
	free(result_ft);
	return (test_count + 1);
}

int	itoa_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = itoa_cmp(test_count, 0, "0");
	test_count = itoa_cmp(test_count, 1, "1");
	test_count = itoa_cmp(test_count, 12, "12");
	test_count = itoa_cmp(test_count, 123, "123");
	test_count = itoa_cmp(test_count, 1234, "1234");
	test_count = itoa_cmp(test_count, 12345, "12345");
	test_count = itoa_cmp(test_count, -123456, "-123456");
	test_count = itoa_cmp(test_count, INT_MAX, "2147483647");
	test_count = itoa_cmp(test_count, INT_MIN, "-2147483648");
	return (g_fail_itoa);
}
