/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:12:54 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/30 18:37:01 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int	g_fc = 0;

char	*init_ft_calloc(size_t nmemb, size_t n)
{
	char	*ftc;

	ftc = ft_calloc(nmemb, n);
	if (ftc == NULL)
	{
		printf("calloc error\n");
		return (NULL);
	}
	return (ftc);
}

char	*init_calloc(size_t nmemb, size_t n)
{
	char	*c;

	c = calloc(nmemb, n);
	if (c == NULL)
	{
		printf("calloc error\n");
		return (NULL);
	}
	return (c);
}

void	print_console(int test_count, int color, size_t nmemb, size_t n)
{
	if (!color)
	{
		if (test_count / 10 == 0)
			printf(RED "%d:  FAIL: \"%zu, %zu\"\n" RESET, test_count, nmemb, n);
		else
			printf(RED "%d: FAIL: \"%zu, %zu\"\n" RESET, test_count, nmemb, n);
	}
	else
	{
		if (test_count / 10 == 0)
			printf(GRN "%d:  OK: \"%zu, %zu\"\n" RESET, test_count, nmemb, n);
		else
			printf(GRN "%d: OK: \"%zu, %zu\"\n" RESET, test_count, nmemb, n);
	}
}

int	calloc_cmp(int test_count, size_t nmemb, size_t n)
{
	char	*c;
	char	*ftc;
	size_t	ei;
	int		fail_check;

	ei = 0;
	c = init_calloc(nmemb, n);
	ftc = init_ft_calloc(nmemb, n);
	if (c == NULL || ftc == NULL)
		return (1);
	fail_check = g_fc;
	while (ei != (nmemb * n))
	{
		if ((char)c[ei] != (char)ftc[ei])
		{
			g_fc += ft_log_chr(test_count, (char)c[ei], (char)ftc[ei]);
			dprintf(2, "tcase: [nmemb] %zu [n] %zu\n", nmemb, n);
			break ;
		}
		ei++;
	}
	print_console(test_count, (fail_check == g_fc), nmemb, n);
	free(c);
	free(ftc);
	return (test_count + 1);
}

void	more_calloc_test(int *test_count)
{
	*test_count = calloc_cmp(*test_count, 1, sizeof(char));
	*test_count = calloc_cmp(*test_count, 1000, sizeof(char));
	*test_count = calloc_cmp(*test_count, 1000000, sizeof(char));
	*test_count = calloc_cmp(*test_count, 1, sizeof(int));
	*test_count = calloc_cmp(*test_count, 1000, sizeof(int));
	*test_count = calloc_cmp(*test_count, 1000000, sizeof(int));
	*test_count = calloc_cmp(*test_count, 1, sizeof(float));
	*test_count = calloc_cmp(*test_count, 1000, sizeof(float));
	*test_count = calloc_cmp(*test_count, 1000000, sizeof(float));
	*test_count = calloc_cmp(*test_count, 1, sizeof(void));
	*test_count = calloc_cmp(*test_count, 1000, sizeof(void));
	*test_count = calloc_cmp(*test_count, 1000000, sizeof(void));
}

int	calloc_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = calloc_cmp(test_count, 0, 0);
	test_count = calloc_cmp(test_count, 1, 1);
	test_count = calloc_cmp(test_count, 5, 1);
	test_count = calloc_cmp(test_count, 5, 0);
	test_count = calloc_cmp(test_count, 1, 5);
	test_count = calloc_cmp(test_count, 0, 5);
	test_count = calloc_cmp(test_count, 1, 0);
	test_count = calloc_cmp(test_count, 1000, 0);
	test_count = calloc_cmp(test_count, 1000000, 0);
	test_count = calloc_cmp(test_count, 0, 1);
	test_count = calloc_cmp(test_count, 0, 1000);
	test_count = calloc_cmp(test_count, 0, 1000000);
	more_calloc_test(&test_count);
	return (g_fc);
}
