/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 17:08:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 14:52:43 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>
#include <fcntl.h>

int	g_fail_putstr = 0;

int	comparefile_putstr(FILE *fPtr1, char *test, int *line, int *col)
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
			return (-1);
		index++;
	}
	return (0);
}

int	compare_files_str(int test_count, char *test)
{
	int		line;
	int		col;
	FILE	*fptr;
	FILE	*errorlog;

	fptr = fopen("libft_tests/putstr_ft.txt", "r");
	errorlog = fopen("logs/error_log.txt", "a");
	if (fptr == NULL || errorlog == NULL)
	{
		printf("\nUnable to open file.\n");
		return (-1);
	}
	if (comparefile_putstr(fptr, test, &line, &col) != 0)
		g_fail_putstr += ft_log_int(test_count, errorlog, line, col);
	rewind(fptr);
	fclose(fptr);
	fclose(errorlog);
	return (0);
}

int	putstr_cmp(int test_count, char *test)
{
	int	fd;

	fclose(fopen("libft_tests/putstr_ft.txt", "w"));
	fd = open("libft_tests/putstr_ft.txt", O_RDWR);
	ft_putstr_fd(test, fd);
	close(fd);
	compare_files_str(test_count, test);
	if (g_fail_putstr == 0)
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	putstr_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = putstr_cmp(test_count, "a");
	test_count = putstr_cmp(test_count, "b");
	test_count = putstr_cmp(test_count, "\200");
	test_count = putstr_cmp(test_count, "\n");
	test_count = putstr_cmp(test_count, "%");
	test_count = putstr_cmp(test_count, " ");
	test_count = putstr_cmp(test_count, "_");
	test_count = putstr_cmp(test_count, "safds_");
	return (g_fail_putstr);
}
