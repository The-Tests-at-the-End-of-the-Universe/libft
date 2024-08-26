/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_tester.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 12:54:09 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 14:50:04 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tester.h"
#include <ctype.h>

int	mem_tests(char *argv)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_memcpy", 9))
		fail += memcpy_test();
	else if (!strncmp(argv, "ft_memchr", 9))
		fail += memchr_test();
	else if (!strncmp(argv, "ft_memmove", 9))
		fail += memmove_test();
	else if (!strncmp(argv, "ft_strlcat", 10))
		fail += strlcat_test();
	else if (!strncmp(argv, "ft_memset", 8))
		fail += memset_test();
	else if (!strncmp(argv, "ft_bzero", 5))
		fail += bzero_test();
	else if (!strncmp(argv, "ft_calloc", 6))
		fail += calloc_test();
	else if (!strncmp(argv, "ft_strdup", 9))
		fail += strdup_test();
	else if (!strncmp(argv, "ft_split", 8))
		fail += split_test();
	else if (!strncmp(argv, "ft_strjoin", 10))
		fail += strjoin_test();
	return (fail);
}

int	write_tests(char *argv)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_putchar", 10))
		fail += putchar_test();
	else if (!strncmp(argv, "ft_putendl", 10))
		fail += putendl_test();
	else if (!strncmp(argv, "ft_putstr", 9))
		fail += putstr_test();
	else if (!strncmp(argv, "ft_putnbr", 9))
		fail += putnbr_test();
	return (fail);
}

int	appendix(char *argv)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_itoa", 7))
		fail += itoa_test();
	if (!strncmp(argv, "ft_atoi", 4))
		fail += atoi_test();
	else if (!strncmp(argv, "ft_isalnum", 10))
		fail += isto_test("ft_isalnum", isalnum, ft_isalnum);
	else if (!strncmp(argv, "ft_isalpha", 10))
		fail += isto_test("ft_isalpha", isalpha, ft_isalpha);
	else if (!strncmp(argv, "ft_isascii", 10))
		fail += isto_test("ft_isascii", isascii, ft_isascii);
	else if (!strncmp(argv, "ft_isdigit", 10))
		fail += isto_test("ft_isdigit", isdigit, ft_isdigit);
	else if (!strncmp(argv, "ft_isprint", 10))
		fail += isto_test("ft_isprint", isprint, ft_isprint);
	else if (!strncmp(argv, "ft_tolower", 10))
		fail += isto_test("ft_tolower", tolower, ft_tolower);
	else if (!strncmp(argv, "ft_toupper", 10))
		fail += isto_test("ft_toupper", toupper, ft_toupper);
	else if (!strncmp(argv, "ft_memcmp", 9))
		fail += memcmp_test();
	return (fail);
}

int	str_tests(char *argv)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_strchr", 9))
		fail += strchr_test();
	else if (!strncmp(argv, "ft_striteri", 11))
		fail += striteri_test();
	else if (!strncmp(argv, "ft_strlcpy", 10))
		fail += strlcpy_test();
	else if (!strncmp(argv, "ft_strlen", 9))
		fail += strlen_test();
	else if (!strncmp(argv, "ft_strmapi", 10))
		fail += strmapi_test();
	else if (!strncmp(argv, "ft_strncmp", 10))
		fail += strncmp_test();
	else if (!strncmp(argv, "ft_strnstr", 10))
		fail += strnstr_test();
	else if (!strncmp(argv, "ft_strrchr", 10))
		fail += strrchr_test();
	else if (!strncmp(argv, "ft_substr", 9))
		fail += substr_test();
	else if (!strncmp(argv, "ft_strtrim", 10))
		fail += strtrim_test();
	return (fail);
}

int	main(int argc, char **argv)
{
	int	fail;

	fail = 0;
	if (argc == 1 || argv == NULL)
		return (printf(RED "wrong parameters given\n" RESET), 1);
	fail += str_tests(argv[1]);
	fail += mem_tests(argv[1]);
	fail += write_tests(argv[1]);
	fail += appendix(argv[1]);
	if (fail > 0)
		printf(RED "\nThere was an error. Check error_log.txt\n" RESET);
	printf("\n");
	return (fail);
}
