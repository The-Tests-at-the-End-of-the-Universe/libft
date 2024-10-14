/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_tester.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 10:53:35 by mynodeus      ########   odam.nl         */
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
# include <stdint.h>

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

int	atoi_test(int test_count, char* fail_flag);
int	bzero_test(int test_count, char* fail_flag);
int	calloc_test(int test_count, char* fail_flag);
int	isto_test(int test_count, int (*f)(int), int (*ft)(int), char *fail_flag);
int	itoa_test(int test_count, char* fail_flag);
int	memchr_test(int test_count, char* fail_flag);
int	memcmp_test(int test_count, char* fail_flag);
int	memcpy_test(int test_count, char* fail_flag);
int	memmove_test(int test_count, char* fail_flag);
int	memset_test(int test_count, char* fail_flag);
int	putchar_test(int test_count, char* fail_flag);
int	putendl_test(int test_count, char* fail_flag);
int	putnbr_test(int test_count, char* fail_flag);
int	putstr_test(int test_count, char* fail_flag);
int	split_test(int test_count, char* fail_flag);
int	strchr_test(int test_count, char* fail_flag);
int	strdup_test(int test_count, char* fail_flag);
int	striteri_test(int test_count, char* fail_flag);
int	strjoin_test(int test_count, char* fail_flag);
int	strlcat_test(int test_count, char *fail_flag);
int	strlcpy_test(int test_count, char *fail_flag);
int	strlen_test(int test_count, char *fail_flag);
int	strmapi_test(int test_count, char *fail_flag);
int	strncmp_test(int test_count, char *fail_flag);
int	strnstr_test(int test_count, char *fail_flag);
int	strrchr_test(int test_count, char *fail_flag);
int	strtrim_test(int test_count, char *fail_flag);
int	substr_test(int test_count);
int	ft_log_int(int test_count, int result_org, int result_ft);
int	ft_log_str(int test_count, char *ro, char *rft);
int	ft_log_chr(int test_count, char ro, char rft);
int	wait_child(int pid);
void	*create_shared_memory(size_t size);
int	chrcmp(char *org, char *ft, size_t n);

#endif
