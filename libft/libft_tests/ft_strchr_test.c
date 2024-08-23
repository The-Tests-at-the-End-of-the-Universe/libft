/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:44:11 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/17 05:50:43 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strchr = 0;

int	strchr_cmp(int test_count, char *test, int ch)
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
	org = strchr(test, ch);
	ft = ft_strchr(test, ch);
	if (org != ft)
		g_fail_strchr += ft_log_str(test_count, errorlog, org, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	strchr_test(void)
{
	int	test_count;

	test_count = 1;
	printf("\n");
	printf(BMAG "ft_strchr\n" RESET);
	test_count = strchr_cmp(test_count, "nfdsnkjdsnciudsbccknd?cbdscds", '?');
	test_count = strchr_cmp(test_count, "bobobbocobedbobobbobob!", '!');
	test_count = strchr_cmp(test_count, "a", 'b');
	test_count = strchr_cmp(test_count, "dfsfdsf???cbdscds", '?');
	test_count = strchr_cmp(test_count, "sdncdskj nkjsanckjdsncj\ndkj", '\n');
	return (g_fail_strchr);
}
