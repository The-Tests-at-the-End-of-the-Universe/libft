/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_tester.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/27 18:31:37 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TESTER_H
# define LIBFT_TESTER_H

//these inclusions are needed to be able to use the write function from
// unistd library. and malloc and free from the stdlib library.

# include <stdio.h>
# include "../../libft.h"
# include <stdlib.h>
# include <limits.h>
# include <string.h>

# define RED   "\x1B[31m"
# define GRN   "\x1B[1;32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define BMAG   "\x1B[1;35m"
# define CYN   "\x1B[36m"
# define BCYN   "\x1B[1;36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

int	atoi_test(void);
int	bzero_test(void);
int	calloc_test(void);
int	isto_test(char *function_name, int (*f)(int), int (*ft)(int));
int	itoa_test(void);
int	memchr_test(void);
int	memcmp_test(void);
int	memcpy_test(void);
int	memmove_test(void);
int	memset_test(void);
int	putchar_test(void);
int	putendl_test(void);
int	putstr_test(void);
int	putnbr_test(void);
int	split_test(void);
int	strchr_test(void);
int	strdup_test(void);
int	striteri_test(void);
int	strjoin_test(void);
int	strlcat_test(void);
int	strlcpy_test(void);
int	strlen_test(void);
int	strmapi_test(void);
int	strncmp_test(void);
int	strnstr_test(void);
int	strrchr_test(void);
int	substr_test(void);
int	strtrim_test(void);
int	ft_log_int(int test_count, int result_org, int result_ft);
int	ft_log_str(int test_count, char *ro, char *rft);
int	ft_log_chr(int test_count, char ro, char rft);
#endif
