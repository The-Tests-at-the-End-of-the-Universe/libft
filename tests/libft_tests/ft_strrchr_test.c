/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/26 16:34:09 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <bsd/string.h>

int	g_fail_strrchr = 0;

int	strrchr_cmp(int test_count, char *test1, char test2)
{
	char	*ft;
	char	*org;

	org = strrchr(test1, test2);
	ft = ft_strrchr(test1, test2);
	if (ft != org)
		g_fail_strrchr += ft_log_str(test_count, org, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	strrchr_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = strrchr_cmp(test_count, "nfdsnkjdsnciudsbccknd?cbdscds", '?');
	test_count = strrchr_cmp(test_count, "bobobbocobedbobobbobob!", '!');
	test_count = strrchr_cmp(test_count, "a", 'b');
	test_count = strrchr_cmp(test_count, "dfsfdsf???cbdscds", '?');
	test_count = strrchr_cmp(test_count, "sdncdskj nkjsanckjdsncj\ndkj", '\n');
	return (g_fail_strrchr);
}
