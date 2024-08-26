/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 17:08:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 16:22:26 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>
#include <fcntl.h>

int	g_fail_putchar = 0;

int	comparefile(FILE *fptr, char test, int *line, int *col)
{
	char	ch1;
	char	ch2;

	*line = 1;
	*col = 0;
	ch1 = fgetc(fptr);
	ch2 = test;
	if (ch1 != ch2)
		return (-1);
	return (0);
}

int	compare_files(int test_count, char test)
{
	int		line;
	int		col;
	FILE	*fptr;

	fptr = fopen("libft_tests/putchar_ft.txt", "r");
	if (fptr == NULL)
	{
		printf("\nUnable to open file.\n");
		return (-1);
	}
	if (comparefile(fptr, test, &line, &col) != 0)
		g_fail_putchar += ft_log_int(test_count, line, col);
	rewind(fptr);
	fclose(fptr);
	return (0);
}

int	putchar_cmp(int test_count, int test)
{
	int	fd;

	fclose(fopen("libft_tests/putchar_ft.txt", "w"));
	fd = open("libft_tests/putchar_ft.txt", O_RDWR);
	ft_putchar_fd(test, fd);
	close(fd);
	compare_files(test_count, test);
	if (g_fail_putchar == 0)
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	putchar_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = putchar_cmp(test_count, 'a');
	test_count = putchar_cmp(test_count, 'b');
	test_count = putchar_cmp(test_count, '\200');
	test_count = putchar_cmp(test_count, '\n');
	test_count = putchar_cmp(test_count, '%');
	test_count = putchar_cmp(test_count, 0);
	test_count = putchar_cmp(test_count, ' ');
	test_count = putchar_cmp(test_count, '_');
	return (g_fail_putchar);
}
