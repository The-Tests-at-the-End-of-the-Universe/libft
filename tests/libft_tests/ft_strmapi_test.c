/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:33:32 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/27 16:09:15 by spenning      ########   odam.nl         */
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
	char	*ft_result;
	char	*test_dub;

	test_dub = strdup(test);
	ft_result = ft_strmapi(test_dub, &test_function_mapi);
	if (strcmp(ft_result, result))
	{
		g_fail_strmapi += ft_log_str(test_count, test, test_dub);
		dprintf(2, "tcase: [str] %s [result] %s\n", test, result);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	free(ft_result);
	free(test_dub);
	return (test_count + 1);
}

int	strmapi_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = strmapi_cmp(test_count, "123", "135");
	test_count = strmapi_cmp(test_count, "abc", "ace");
	test_count = strmapi_cmp(test_count, "ABC", "ACE");
	return (g_fail_strmapi);
}
