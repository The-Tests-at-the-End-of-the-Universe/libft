/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:12:54 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/29 17:57:36 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fc = 0;

typedef struct s_calloc_test
{
	size_t	nmemb;
	size_t	n;
}	t_calloc_test;

static const t_calloc_test	g_tests[] = {
[ZERO] = {1, sizeof(char)},
[ONE] = {1000, sizeof(char)},
[TWO] = {1000000, sizeof(char)},
[THREE] = {1, sizeof(int)},
[FOUR] = {1000, sizeof(int)},
[FIVE] = {1000000, sizeof(int)},
[SIX] = {1, sizeof(float)},
[SEVEN] = {1000, sizeof(float)},
[EIGHT] = {1000000, sizeof(float)},
[NINE] = {1, sizeof(void)},
[TEN] = {1000, sizeof(void)},
[ELEVEN] = {1000000, sizeof(void)},
[TWELVE] = {1, 0},
[THIRTEEN] = {1000, 0},
[FOURTEEN] = {1000000, 0},
[FIVETEEN] = {0, 1},
[SIXTEEN] = {0, 1000},
[SEVENTEEN] = {0, 1000000},
[EIGHTEEN] = {0, 0},
[NINETEEN] = {1, 1},
[TWENTY] = {5, 1},
[TWENTYONE] = {5, 0},
[TWENTYTWO] = {1, 5},
[TWENTYTHREE] = {0, 5},
};

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

int	calloc_cmp(int test_count)
{
	char	*c;
	char	*ftc;
	size_t	ei;

	ei = 0;
	c = init_calloc(tests[test_count].nmemb, tests[test_count].nmemb);
	ftc = init_ft_calloc(tests[test_count].nmemb, tests[test_count].nmemb);
	if (c == NULL || ftc == NULL)
		return (1);
	while (ei != (tests[test_count].nmemb * tests[test_count].nmemb))
	{
		if ((char)c[ei] != (char)ftc[ei])
		{
			g_fc += ft_log_chr(test_count, (char)c[ei], (char)ftc[ei]);
			dprintf(2, "tcase: [nmemb] %zu [n] %zu\n", \
			tests[test_count].nmemb, tests[test_count].nmemb);
		}
		ei++;
	}
	printf(GRN "%d OK " RESET, test_count);
	free(c);
	free(ftc);
	return (test_count + 1);
}

int	calloc_test(int test_count)
{
	if (test_count == sizeof(tests) / sizeof(tests[0]))
		return (FINISH);
	calloc_cmp(int test_count)
	return (g_fc);
}
