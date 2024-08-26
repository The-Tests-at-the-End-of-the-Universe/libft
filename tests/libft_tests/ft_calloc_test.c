/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:12:54 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 14:51:57 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
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

FILE	*init_elog(void)
{
	FILE	*elog;

	elog = fopen("logs/error_log.txt", "a");
	if (elog == NULL)
	{
		printf("Error opening log file\n");
		return (NULL);
	}
	return (elog);
}

int	calloc_cmp(int test_count, size_t nmemb, size_t n)
{
	FILE	*elog;
	char	*c;
	char	*ftc;
	size_t	ei;

	ei = 0;
	elog = init_elog();
	c = init_calloc(nmemb, n);
	ftc = init_ft_calloc(nmemb, n);
	if (elog == NULL || c == NULL || ftc == NULL)
		return (1);
	while (ei != (nmemb * n))
	{
		if ((char)c[ei] != (char)ftc[ei])
			g_fc += ft_log_chr(test_count, elog, (char)c[ei], (char)ftc[ei]);
		ei++;
	}
	printf(GRN "%d OK " RESET, test_count);
	free(c);
	free(ftc);
	fclose(elog);
	return (test_count + 1);
}

int	calloc_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = calloc_cmp(test_count, 1, sizeof(char));
	test_count = calloc_cmp(test_count, 1000, sizeof(char));
	test_count = calloc_cmp(test_count, 1000000, sizeof(char));
	test_count = calloc_cmp(test_count, 1, sizeof(int));
	test_count = calloc_cmp(test_count, 1000, sizeof(int));
	test_count = calloc_cmp(test_count, 1000000, sizeof(int));
	test_count = calloc_cmp(test_count, 1, sizeof(float));
	test_count = calloc_cmp(test_count, 1000, sizeof(float));
	test_count = calloc_cmp(test_count, 1000000, sizeof(float));
	test_count = calloc_cmp(test_count, 1, sizeof(void));
	test_count = calloc_cmp(test_count, 1000, sizeof(void));
	test_count = calloc_cmp(test_count, 1000000, sizeof(void));
	test_count = calloc_cmp(test_count, 1, 0);
	test_count = calloc_cmp(test_count, 1000, 0);
	test_count = calloc_cmp(test_count, 1000000, 0);
	test_count = calloc_cmp(test_count, 0, 1);
	test_count = calloc_cmp(test_count, 0, 1000);
	test_count = calloc_cmp(test_count, 0, 1000000);
	return (g_fc);
}
