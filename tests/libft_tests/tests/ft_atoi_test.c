/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/30 17:41:40 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>

int	g_fail_atoi = 0;

int	atoi_cmp(int test_count, char *test)
{
	int		result_org;
	int		result_ft;

	result_org = atoi(test);
	result_ft = ft_atoi(test);
	if (result_org != result_ft)
	{
		g_fail_atoi += ft_log_int(test_count, result_org, result_ft);
		dprintf(2, "tcase: %s\n", test);
	}
	else
	{
		if (test_count / 10 == 0)
			printf(GRN "%d:  OK: \"%s\"\n" RESET, test_count, test);
		else
			printf(GRN "%d: OK: \"%s\"\n" RESET, test_count, test);
	}
	return (test_count + 1);
}

void	atoi_test_more(int *test_count)
{
	*test_count = atoi_cmp(*test_count, "-00123");
	*test_count = atoi_cmp(*test_count, "--00123");
	*test_count = atoi_cmp(*test_count, "---00123");
	*test_count = atoi_cmp(*test_count, "-+-+-00123");
	*test_count = atoi_cmp(*test_count, "++00123");
	*test_count = atoi_cmp(*test_count, "++--00123");
	*test_count = atoi_cmp(*test_count, "  -00123");
	*test_count = atoi_cmp(*test_count, "		--00123");
	*test_count = atoi_cmp(*test_count, "	 	 ---00123");
	*test_count = atoi_cmp(*test_count, "	 	 -+-+-00123");
	*test_count = atoi_cmp(*test_count, "	 	 ++00123");
	*test_count = atoi_cmp(*test_count, "	 	 ++--00123");
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
	test_count = atoi_cmp(test_count, "       ");
	atoi_test_more(&test_count);
	return (g_fail_atoi);
}
