/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 23:03:23 by spenning          #+#    #+#             */
/*   Updated: 2024/05/16 13:04:08 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"

int	g_fail_atoi = 0;

int	atoi_cmp(int test_count, char *test)
{
	FILE	*errorlog;
	int		result_org;
	int		result_ft;

	result_org = 0;
	result_ft = 0;
	errorlog = fopen("logs/error_log.txt", "a");
	if (errorlog == NULL)
	{
		printf("Error opening log file\n");
		return (1);
	}
	result_org = atoi(test);
	result_ft = ft_atoi(test);
	if (result_org != result_ft)
	{
		fprintf(errorlog, "ft_atoi\n");
		g_fail_atoi += ft_log_int(test_count, errorlog, result_org, result_ft);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	atoi_test(void)
{
	int	test_count;

	test_count = 1;
	printf("\n");
	printf(BMAG "ft_atoi\n" RESET);
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
