/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero_test.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 12:48:45 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/29 17:58:36 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int	g_fail_bzero = 0;

typedef struct s_bzero_test
{
	char	*string;
	int		num;
} t_bzero_test;


// struct Student students[] = { { "John", 1, 85.5 },
//                                   { "Emma", 2, 90.6 },
//                                   { "Harry", 3, 92.7 } };

static const t_bzero_test tests[] = {
	[ZERO] = {"", 0},
	[ONE] = {"1", 1},
	// [TWO] = "12",
	// [THREE] = "123",
	// [FOUR] = "1234",
	// [FIVE] = "  12345",
	// [SIX] = "  12345",
	// [SEVEN] = "123 456",
	// [EIGHT] = "A2143244535",
	// [NINE] = "2143244535",
	// [TEN] = "",
	// [ELEVEN] = "asbj",
	// [TWELVE] = "",
	// [THIRTEEN] = "       ",
	// [FOURTEEN] = "-00123",
	// [FIVETEEN] = "--00123",
	// [SIXTEEN] = "-+-+-00123",
	// [SEVENTEEN] = "-+-+-00123",
	// [EIGHTEEN] = "++00123",
	// [NINETEEN] = "++--00123",
	// [TWENTY] = "  -00123",
	// [TWENTYONE] = "		--00123",
	// [TWENTYTWO] = "	 	 ---00123",
};


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
		g_fail_bzero = 1;
	}
	else
		g_fail_bzero = 0;
	free(ta);
	free(td);
	return (test_count + 1);
}

int	bzero_cmp(int test_count)
{
	char	*test_alloc;
	char	*test_dup;

	if (!tests[test_count].string)
		return (1);
	test_alloc = init_test_alloc(tests[test_count].string);
	if (test_alloc == NULL)
		return (1);
	test_dup = init_test_dup(tests[test_count].string, test_alloc);
	if (test_dup == NULL)
		return (1);
	bzero(test_alloc, tests[test_count].num);
	ft_bzero(test_dup, tests[test_count].num);
	return (bzero_cmp_exe(test_alloc, test_dup, test_count, tests[test_count].string));
}

int	bzero_test(int test_count)
{

	if (test_count == sizeof(tests) / sizeof(tests[0]))
		return (FINISH);
	bzero_cmp(test_count);

	// test_count = 1;
	// test_count = bzero_cmp(test_count, "1", 1);
	// test_count = bzero_cmp(test_count, "12", 1);
	// test_count = bzero_cmp(test_count, "123", 2);
	// test_count = bzero_cmp(test_count, "1234", 2);
	// test_count = bzero_cmp(test_count, "  12345", 5);
	// test_count = bzero_cmp(test_count, "123 456", 5);
	// test_count = bzero_cmp(test_count, "A2143244535", 7);
	// test_count = bzero_cmp(test_count, "2143244535", 7);
	// test_count = bzero_cmp(test_count, " ", 1);
	// test_count = bzero_cmp(test_count, "asbj", 4);
	// test_count = bzero_cmp(test_count, "       ", 1);

	return (g_fail_bzero);
}
