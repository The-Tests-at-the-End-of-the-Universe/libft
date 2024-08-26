/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 15:52:53 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"

int	g_fail_atoi = 0;

int	atoi_cmp(int test_count, char *test)
{
	int		result_org;
	int		result_ft;

	result_org = atoi(test);
	result_ft = ft_atoi(test);
	if (result_org != result_ft)
		g_fail_atoi += ft_log_int(test_count, result_org, result_ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	atoi_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = atoi_cmp(test_count, "1");
	test_count = atoi_cmp(test_count, "12");
	test_count = atoi_cmp(test_count, "123");
	test_count = atoi_cmp(test_count, "1234");
	test_count = atoi_cmp(test_count, "  12345");
	test_count = atoi_cmp(test_count, "123 456");
	test_count = atoi_cmp(test_count, "A2143244535");
	test_count = atoi_cmp(test_count, "2143244535");
	test_count = atoi_cmp(test_count, "");
	test_count = atoi_cmp(test_count, "asbj");
	test_count = atoi_cmp(test_count, "");
	test_count = atoi_cmp(test_count, "       ");
	return (g_fail_atoi);
}
