/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:28:06 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/27 14:41:50 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_split = 0;

int	cmp_split(char **ft_result, char *test, char *delim)
{
	int		index;
	char	*testret;
	char	*rest;
	char	*begin;

	index = 0;
	rest = strdup(test);
	begin = rest;
	while (ft_result[index] != NULL)
	{
		testret = __strtok_r(rest, delim, &rest);
		if (strcmp(testret, ft_result[index]))
		{
			free(begin);
			return (-1);
		}
		index++;
	}
	free(begin);
	return (0);
}

int	split_cmp(int test_count, char *test, char *delim)
{
	char	**array;
	int		index;

	index = 0;
	array = ft_split(test, delim[0]);
	if (cmp_split(array, test, delim) != 0)
		g_fail_split += ft_log_str(test_count, test, delim);
	else
		printf(GRN "%d OK " RESET, test_count);
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
	return (0);
}

int	split_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = split_cmp(test_count, "aaa;bbb,", ";");
	test_count = split_cmp(test_count, "kokokokokokokoko", "o");
	test_count = split_cmp(test_count, "hdkjsahdkjsa|hdkjsahdkjsa", "|");
	test_count = split_cmp(test_count, "aaaa////aaaa//aa///", "/");
	return (g_fail_split);
}
