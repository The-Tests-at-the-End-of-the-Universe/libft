/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_tester.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 12:54:09 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/06 21:47:08 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <ctype.h>

int	mem_tests(char *argv, int test_count)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_memcpy", 9))
		fail += memcpy_test(test_count);
	else if (!strncmp(argv, "ft_memchr", 9))
		fail += memchr_test(test_count);
	else if (!strncmp(argv, "ft_memmove", 9))
		fail += memmove_test(test_count);
	else if (!strncmp(argv, "ft_strlcat", 10))
		fail += strlcat_test(test_count);
	else if (!strncmp(argv, "ft_memset", 8))
		fail += memset_test(test_count);
	else if (!strncmp(argv, "ft_bzero", 5))
		fail += bzero_test(test_count);
	else if (!strncmp(argv, "ft_calloc", 6))
		fail += calloc_test(test_count);
	else if (!strncmp(argv, "ft_strdup", 9))
		fail += strdup_test(test_count);
	else if (!strncmp(argv, "ft_split", 8))
		fail += split_test(test_count);
	else if (!strncmp(argv, "ft_strjoin", 10))
		fail += strjoin_test(test_count);
	return (fail);
}

int	write_tests(char *argv, int test_count)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_putchar_fd", 10))
		fail += putchar_test(test_count);
	else if (!strncmp(argv, "ft_putendl_fd", 10))
		fail += putendl_test(test_count);
	else if (!strncmp(argv, "ft_putnbr_fd", 9))
		fail += putnbr_test(test_count);
	else if (!strncmp(argv, "ft_putstr_fd", 9))
		fail += putstr_test(test_count);
	return (fail);
}

int	appendix(char *argv, int test_count)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_itoa", 7))
		fail += itoa_test(test_count);
	if (!strncmp(argv, "ft_atoi", 4))
		fail += atoi_test(test_count);
	else if (!strncmp(argv, "ft_isalnum", 10))
		fail += isto_test(test_count, isalnum, ft_isalnum);
	else if (!strncmp(argv, "ft_isalpha", 10))
		fail += isto_test(test_count, isalpha, ft_isalpha);
	else if (!strncmp(argv, "ft_isascii", 10))
		fail += isto_test(test_count, isascii, ft_isascii);
	else if (!strncmp(argv, "ft_isdigit", 10))
		fail += isto_test(test_count, isdigit, ft_isdigit);
	else if (!strncmp(argv, "ft_isprint", 10))
		fail += isto_test(test_count, isprint, ft_isprint);
	else if (!strncmp(argv, "ft_tolower", 10))
		fail += isto_test(test_count, tolower, ft_tolower);
	else if (!strncmp(argv, "ft_toupper", 10))
		fail += isto_test(test_count, toupper, ft_toupper);
	else if (!strncmp(argv, "ft_memcmp", 9))
		fail += memcmp_test(test_count);
	return (fail);
}

int	str_tests(char *argv, int test_count)
{
	int	fail;

	fail = 0;
	if (!strncmp(argv, "ft_strchr", 9))
		fail += strchr_test(test_count);
	else if (!strncmp(argv, "ft_striteri", 11))
		fail += striteri_test(test_count);
	else if (!strncmp(argv, "ft_strlcpy", 10))
		fail += strlcpy_test(test_count);
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
	int	test_count;

	test_count = atoi(argv[2]);
	fail = 0;
	if (argc == 1 || argv == NULL)
		return (printf(RED "wrong parameters given\n" RESET), 1);
	fail += str_tests(argv[1], test_count);
	fail += mem_tests(argv[1], test_count);
	fail += write_tests(argv[1], test_count);
	fail += appendix(argv[1], test_count);
	return (fail);
}
