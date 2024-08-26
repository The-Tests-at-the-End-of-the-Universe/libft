/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/26 16:32:38 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strncmp = 0;

int	strncmp_cmp(int test_count, char *test1, char *test2, size_t n)
{
	size_t	ft;
	size_t	org;

	org = strncmp(test1, test2, n);
	ft = ft_strncmp(test1, test2, n);
	if (ft != org)
		g_fail_strncmp += ft_log_int(test_count, org, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	strncmp_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = strncmp_cmp(test_count, "nfdsnkjd", "dlksadbs", 16);
	test_count = strncmp_cmp(test_count, "bobobbocob", "dlksadbs", 18);
	test_count = strncmp_cmp(test_count, "a", "b", 2);
	test_count = strncmp_cmp(test_count, "dfsfdsf?", "??cbdscds", 17);
	test_count = strncmp_cmp(test_count, "", "", 0);
	test_count = strncmp_cmp(test_count, " ", " ", 2);
	return (g_fail_strncmp);
}
