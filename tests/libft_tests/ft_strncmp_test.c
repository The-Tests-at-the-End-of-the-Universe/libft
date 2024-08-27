/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/27 16:10:48 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strncmp = 0;

//added multiple conditions because returns value of strncmp can differ
//per compiler
//https://stackoverflow.com/questions/52334056/weird-return-value-in-strcmp
int	strncmp_cmp(int test_count, char *test1, char *test2, int n)
{
	int	ft;
	int	org;

	org = strncmp(test1, test2, n);
	ft = ft_strncmp(test1, test2, n);
	if (ft < 0 && org < 0)
		printf(GRN "%d OK " RESET, test_count);
	else if (ft > 0 && org > 0)
		printf(GRN "%d OK " RESET, test_count);
	else if (ft == 0 && org == 0)
		printf(GRN "%d OK " RESET, test_count);
	else
	{
		g_fail_strncmp += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %s [2] %s [n] %d\n", test1, test2, n);
	}
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
