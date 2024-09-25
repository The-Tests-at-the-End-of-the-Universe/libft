/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:47:38 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:57 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <limits.h>

int							g_fail_itoa = 0;

typedef struct s_itoa_test
{
	int		test;
	char	*test_case;
}	t_itoa_test;

static const t_itoa_test	g_tests[] = {
[ZERO] = {0, "0"},
[ONE] = {1, "1"},
[TWO] = {12, "12"},
[THREE] = {123, "123"},
[FOUR] = {1234, "1234"},
[FIVE] = {12345, "12345"},
[SIX] = {-123456, "-123456"},
[SEVEN] = {INT_MAX, "2147483647"},
[EIGHT] = {INT_MIN, "-2147483648"},
};

int	itoa_cmp(int test_count)
{
	char	*result_org;
	char	*result_ft;

	result_org = g_tests[test_count].test_case;
	result_ft = ft_itoa(g_tests[test_count].test);
	if (result_ft == NULL)
	{
		printf("error with result_ft\n");
		return (1);
	}
	if (strcmp(result_org, result_ft))
	{
		g_fail_itoa += ft_log_str(test_count, result_org, result_ft);
		dprintf(2, "tcase: %d\n", g_tests[test_count].test);
		g_fail_itoa = 1;
	}
	else
		g_fail_itoa = 0;
	free(result_ft);
	return (test_count + 1);
}

int	itoa_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	itoa_cmp(test_count);
	return (g_fail_itoa);
}
