/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri_test.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:52:33 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/26 16:28:36 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_striteri = 0;

void	test_function(unsigned int c, char *s)
{
	s[0] = s[0] + c;
}

int	striteri_cmp(int test_count, char *test, char *result)
{
	char	*test_dub;

	test_dub = strdup(test);
	ft_striteri(test_dub, test_function);
	if (strcmp(test_dub, result))
		g_fail_striteri += ft_log_str(test_count, test, test_dub);
	else
		printf(GRN "%d OK " RESET, test_count);
	free(test_dub);
	return (test_count + 1);
}

int	striteri_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = striteri_cmp(test_count, "123", "135");
	test_count = striteri_cmp(test_count, "abc", "ace");
	test_count = striteri_cmp(test_count, "ABC", "ACE");
	return (g_fail_striteri);
}
