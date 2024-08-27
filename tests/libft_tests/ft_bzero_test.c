/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 12:48:45 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/27 15:57:16 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_bzero = 0;

char	*init_test_dup(char *test, char *test_alloc)
{
	char	*test_dup;

	test_dup = strdup(test);
	if (test)
	{
		if (test_dup == NULL)
		{
			if (test_alloc)
				free(test_alloc);
			printf("Error with creating dup string for testing\n");
			return (NULL);
		}
	}
	return (test_dup);
}

char	*init_test_alloc(char *test)
{
	char	*test_alloc;

	test_alloc = malloc(strlen(test));
	if (test_alloc == NULL)
	{
		printf("Error with creating alloc string for testing\n");
		return (NULL);
	}
	return (test_alloc);
}

int	bzero_cmp_exe(char	*ta, char	*td, int test_count, char *test)
{
	if (strcmp(ta, td))
	{
		g_fail_bzero += ft_log_str(test_count, ta, td);
		dprintf(2, "tcase: %s\n", test);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	free(ta);
	free(td);
	return (test_count + 1);
}

int	bzero_cmp(int test_count, char *test, size_t n)
{
	char	*test_alloc;
	char	*test_dup;

	if (!test)
		return (1);
	test_alloc = init_test_alloc(test);
	if (test_alloc == NULL)
		return (1);
	test_dup = init_test_dup(test, test_alloc);
	if (test_dup == NULL)
		return (1);
	bzero(test_alloc, n);
	ft_bzero(test_dup, n);
	return (bzero_cmp_exe(test_alloc, test_dup, test_count, test));
}

int	bzero_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = bzero_cmp(test_count, "1", 1);
	test_count = bzero_cmp(test_count, "12", 1);
	test_count = bzero_cmp(test_count, "123", 2);
	test_count = bzero_cmp(test_count, "1234", 2);
	test_count = bzero_cmp(test_count, "  12345", 5);
	test_count = bzero_cmp(test_count, "123 456", 5);
	test_count = bzero_cmp(test_count, "A2143244535", 7);
	test_count = bzero_cmp(test_count, "2143244535", 7);
	test_count = bzero_cmp(test_count, " ", 1);
	test_count = bzero_cmp(test_count, "asbj", 4);
	test_count = bzero_cmp(test_count, "       ", 1);
	return (g_fail_bzero);
}
