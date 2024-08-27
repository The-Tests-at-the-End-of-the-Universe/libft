/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:44:11 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/27 16:05:28 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strchr = 0;

int	strchr_cmp(int test_count, char *test, int ch)
{
	char	*org;
	char	*ft;

	org = strchr(test, ch);
	ft = ft_strchr(test, ch);
	if (org != ft)
	{
		g_fail_strchr += ft_log_str(test_count, org, ft);
		dprintf(2, "tcase: [str] %s [ch] %d\n", test, ch);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	strchr_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = strchr_cmp(test_count, "nfdsnkjdsnciudsbccknd?cbdscds", '?');
	test_count = strchr_cmp(test_count, "bobobbocobedbobobbobob!", '!');
	test_count = strchr_cmp(test_count, "a", 'b');
	test_count = strchr_cmp(test_count, "dfsfdsf???cbdscds", '?');
	test_count = strchr_cmp(test_count, "sdncdskj nkjsanckjdsncj\ndkj", '\n');
	return (g_fail_strchr);
}
