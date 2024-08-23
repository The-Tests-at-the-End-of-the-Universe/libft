/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_tester.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 12:54:09 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/07 13:33:13 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tester.h"
#include <ctype.h>

int	appendix(void)
{
	int	fail;

	fail = 0;
	fail += memcpy_test();
	fail += memmove_test();
	fail += memset_test();
	fail += putchar_test();
	fail += putendl_test();
	fail += putstr_test();
	fail += putnbr_test();
	fail += split_test();
	fail += strchr_test();
	fail += strdup_test();
	fail += striteri_test();
	fail += strjoin_test();
	fail += strlcat_test();
	fail += strlcpy_test();
	fail += strlen_test();
	fail += strmapi_test();
	fail += strncmp_test();
	fail += strnstr_test();
	fail += strrchr_test();
	fail += substr_test();
	fail += strtrim_test();
	return (fail);
}

int	main(void)
{
	int	fail;

	fail = 0;
	fclose(fopen("logs/error_log.txt", "w"));
	printf(YEL "\nFunctions" RESET);
	fail += atoi_test();
	fail += bzero_test();
	fail += calloc_test();
	fail += isto_test("ft_isalnum", isalnum, ft_isalnum);
	fail += isto_test("ft_isalpha", isalpha, ft_isalpha);
	fail += isto_test("ft_isascii", isascii, ft_isascii);
	fail += isto_test("ft_isdigit", isdigit, ft_isdigit);
	fail += isto_test("ft_isprint", isprint, ft_isprint);
	fail += isto_test("ft_tolower", tolower, ft_tolower);
	fail += isto_test("ft_toupper", toupper, ft_toupper);
	fail += itoa_test();
	fail += memchr_test();
	fail += memcmp_test();
	fail += appendix();
	if (fail > 0)
		printf(RED "\nThere was an error. Check error_log.txt\n" RESET);
	printf("\n");
	return (0);
}
