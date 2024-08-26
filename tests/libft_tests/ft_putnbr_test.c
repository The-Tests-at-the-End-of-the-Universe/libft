/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 17:08:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 14:52:37 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>
#include <fcntl.h>

int	g_fail_putnbr = 0;

int	comparefile_putnbr(FILE *fPtr1, char *test, int *line, int *col)
{
	char	ch1;
	char	ch2;
	int		index;

	index = 0;
	*line = 1;
	*col = 0;
	ch1 = '\0';
	while (ch1 != EOF)
	{
		ch1 = fgetc(fPtr1);
		ch2 = test[index];
		if (ch1 == EOF)
			return (0);
		if (ch1 != ch2)
		{
			free(test);
			return (-1);
		}
		index++;
	}
	free(test);
	return (0);
}

int	compare_files_nbr(int test_count, int test)
{
	int		line;
	int		col;
	FILE	*fptr;
	FILE	*errorlog;

	fptr = fopen("libft_tests/putnbr_ft.txt", "r");
	errorlog = fopen("logs/error_log.txt", "a");
	if (fptr == NULL || errorlog == NULL)
	{
		printf("\nUnable to open file.\n");
		return (-1);
	}
	if (comparefile_putnbr(fptr, ft_itoa(test), &line, &col) != 0)
		g_fail_putnbr += ft_log_int(test_count, errorlog, line, col);
	rewind(fptr);
	fclose(fptr);
	fclose(errorlog);
	return (0);
}

int	putnbr_cmp(int test_count, int test)
{
	int	fd;

	fclose(fopen("libft_tests/putnbr_ft.txt", "w"));
	fd = open("libft_tests/putnbr_ft.txt", O_RDWR);
	ft_putnbr_fd(test, fd);
	close(fd);
	compare_files_nbr(test_count, test);
	if (g_fail_putnbr == 0)
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	putnbr_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = putnbr_cmp(test_count, 0);
	test_count = putnbr_cmp(test_count, 1);
	test_count = putnbr_cmp(test_count, INT_MAX);
	test_count = putnbr_cmp(test_count, INT_MIN);
	test_count = putnbr_cmp(test_count, 1351546813);
	test_count = putnbr_cmp(test_count, -52454363);
	test_count = putnbr_cmp(test_count, 100);
	test_count = putnbr_cmp(test_count, 999);
	return (g_fail_putnbr);
}
