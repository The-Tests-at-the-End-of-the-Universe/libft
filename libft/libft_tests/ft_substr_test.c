/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 06:51:07 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/17 06:58:46 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int		g_fail_substr = 0;
char	*g_result = NULL;

int	substr_cmp(int test_count, char *test1, int start, size_t len)
{
	FILE	*errorlog;
	char	*ft;

	errorlog = fopen("logs/error_log.txt", "a");
	if (errorlog == NULL)
	{
		printf("Error opening log file\n");
		return (1);
	}
	ft = ft_substr(test1, start, len);
	if (strcmp(ft, g_result))
		g_fail_substr += ft_log_str(test_count, errorlog, g_result, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	free(ft);
	return (test_count + 1);
}

int	substr_test(void)
{
	int	test_count;

	test_count = 1;
	printf("\n");
	printf(BMAG "ft_substr\n" RESET);
	g_result = "kjdsnciu";
	test_count = substr_cmp(test_count, "nfdsnkjdsnciudsbccknd?cbdscds", 5, 8);
	g_result = "bobobbocobedbobobbobob!";
	test_count = substr_cmp(test_count, "bobobbocobedbobobbobob!", 0, 23);
	g_result = "sfdsf???cbdscd";
	test_count = substr_cmp(test_count, "dfsfdsf???cbdscds", 2, 14);
	return (g_fail_substr);
}
