/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:51:07 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/27 16:13:41 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_strtrim = 0;

int	strtrim_cmp(int test_count, char *test1, char *test2, char *result)
{
	char	*ft;

	ft = ft_strtrim(test1, test2);
	if (strcmp(ft, result))
	{
		g_fail_strtrim += ft_log_str(test_count, result, ft);
		dprintf(2, "tcase: [1] %s [2] %s [result] %s\n", test1, test2, result);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	free(ft);
	return (test_count + 1);
}

int	strtrim_test(void)
{
	int	tc;

	tc = 1;
	tc = strtrim_cmp(tc, "aaaaaabaaaaaa", "a", "b");
	tc = strtrim_cmp(tc, "bobobbocobedbobobbo!", "!", "bobobbocobedbobobbo");
	tc = strtrim_cmp(tc, "a", "b", "a");
	tc = strtrim_cmp(tc, "aaaaaabbbbcbbbbaaaaaa", "ab", "c");
	return (g_fail_strtrim);
}
