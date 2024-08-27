/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/27 16:08:36 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strlen = 0;

int	strlen_cmp(int test_count, char *test)
{
	size_t	ft;
	size_t	org;

	org = strlen(test);
	ft = ft_strlen(test);
	if (ft != org)
	{
		g_fail_strlen += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: %s\n", test);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	strlen_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = strlen_cmp(test_count, "nfdsnkjd");
	test_count = strlen_cmp(test_count, "bobobbocob");
	test_count = strlen_cmp(test_count, "a");
	test_count = strlen_cmp(test_count, "dfsfdsf?");
	test_count = strlen_cmp(test_count, "");
	test_count = strlen_cmp(test_count, " ");
	return (g_fail_strlen);
}
