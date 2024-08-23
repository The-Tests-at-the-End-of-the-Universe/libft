/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 06:33:32 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/17 06:36:12 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strmapi = 0;

char	test_function_mapi(unsigned int c, char s)
{
	char	r;

	r = s + c;
	return (r);
}

int	strmapi_cmp(int test_count, char *test, char *result)
{
	FILE	*errorlog;
	char	*ft_result;
	char	*test_dub;

	test_dub = strdup(test);
	errorlog = fopen("logs/error_log.txt", "a");
	if (errorlog == NULL)
	{
		printf("Error opening log file\n");
		return (1);
	}
	ft_result = ft_strmapi(test_dub, &test_function_mapi);
	if (strcmp(ft_result, result))
		g_fail_strmapi += ft_log_str(test_count, errorlog, test, test_dub);
	else
		printf(GRN "%d OK " RESET, test_count);
	free(test_dub);
	return (test_count + 1);
}

int	strmapi_test(void)
{
	int	test_count;

	test_count = 1;
	printf("\n");
	printf(BMAG "ft_strmapi\n" RESET);
	test_count = strmapi_cmp(test_count, "123", "135");
	test_count = strmapi_cmp(test_count, "abc", "ace");
	test_count = strmapi_cmp(test_count, "ABC", "ACE");
	return (g_fail_strmapi);
}
