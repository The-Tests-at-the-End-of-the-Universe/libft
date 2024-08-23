/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istotester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:29:29 by spenning          #+#    #+#             */
/*   Updated: 2024/05/16 13:34:25 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <ctype.h>

int	g_fail_isto = 0;

int	isto_cmp(int tc, int c, int (*f)(int), int (*ft)(int))
{
	FILE	*errorlog;
	int		org_func;
	int		ft_func;

	errorlog = fopen("logs/error_log.txt", "a");
	if (errorlog == NULL)
	{
		printf("Error opening log file\n");
		return (1);
	}
	org_func = f(c);
	ft_func = ft(c);
	if (org_func == 0 && ft_func != 0)
	{
		printf(RED "%d FAIL "RESET, tc);
		fprintf(errorlog, "error\n");
		fprintf(errorlog, "test number: %d\n", tc);
		fprintf(errorlog, "test case: %d\n", c);
		fprintf(errorlog, "---------\n");
		g_fail_isto += 1;
	}
	else
		printf(GRN "%d OK " RESET, tc);
	fclose(errorlog);
	return (tc + 1);
}

int	isto_test(char *function_name, int (*f)(int), int (*ft)(int))
{
	int	test_count;

	test_count = 1;
	printf("\n");
	printf(BMAG "%s\n", function_name);
	printf(RESET);
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
