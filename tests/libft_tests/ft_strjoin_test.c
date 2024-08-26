/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:57:44 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/26 16:29:05 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strjoin = 0;

int	strjoin_cmp(int test_count, char *test1, char *test2, char	*result)
{
	char	*ft;

	ft = ft_strjoin(test1, test2);
	if (strcmp(ft, result))
		g_fail_strjoin += ft_log_str(test_count, result, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	free(ft);
	return (test_count + 1);
}

int	strjoin_test(void)
{
	int	tc;

	tc = 1;
	tc = strjoin_cmp(tc, "nfdsnkjd", "dlksadbs", "nfdsnkjddlksadbs");
	tc = strjoin_cmp(tc, "bobobbocob", "dlksadbs", "bobobbocobdlksadbs");
	tc = strjoin_cmp(tc, "a", "b", "ab");
	tc = strjoin_cmp(tc, "dfsfdsf?", "??cbdscds", "dfsfdsf???cbdscds");
	tc = strjoin_cmp(tc, "", "", "");
	tc = strjoin_cmp(tc, " ", " ", "  ");
	return (g_fail_strjoin);
}
