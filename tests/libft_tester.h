/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_tester.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/09/29 22:03:09 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TESTER_H
# define LIBFT_TESTER_H

//these inclusions are needed to be able to use the write function from
// unistd library. and malloc and free from the stdlib library.

# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <sys/wait.h>
# include <errno.h>

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

# define FINISH 2

enum e_test_count {
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	ELEVEN,
	TWELVE,
	THIRTEEN,
	FOURTEEN,
	FIVETEEN,
	SIXTEEN,
	SEVENTEEN,
	EIGHTEEN,
	NINETEEN,
	TWENTY,
	TWENTYONE,
	TWENTYTWO,
	TWENTYTHREE,
	TWENTYFOUR,
	TWENTYFIVE,
	TWENTYSIX,
	TWENTYSEVEN,
	TWENTYEIGHT,
	TWENTYNINE,
	THIRTY,
};

int	atoi_test(int test_count);
int	bzero_test(int test_count);
int	calloc_test(int test_count);
int	isto_test(int test_count, char *function_name, \
int (*f)(int), int (*ft)(int));
int	itoa_test(int test_count);
int	memchr_test(int test_count);
int	memcmp_test(int test_count);
int	memcpy_test(int test_count);
int	memmove_test(int test_count);
int	memset_test(int test_count);
int	putchar_test(int test_count);
int	putendl_test(int test_count);
int	putnbr_test(int test_count);
int	putstr_test(int test_count);
int	split_test(int test_count);
int	strchr_test(int test_count);
int	strdup_test(int test_count);
int	striteri_test(int test_count);
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
int	wait_child(int pid);
void	*create_shared_memory(size_t size);

#endif
