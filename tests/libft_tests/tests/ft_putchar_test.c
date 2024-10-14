/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 17:08:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 09:16:47 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>
#include <fcntl.h>

int	g_fail_putchar = 0;

int	g_tests[] = {
[0] = 'a',
[1] = 'b',
[2] = '\200',
[3] = '\n',
[4] = '%',
[5] = 0,
[6] = ' ',
[7] = '_',
};

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
	{
		g_fail_putchar += ft_log_int(test_count, line, col);
		dprintf(2, "tcase: %d\n", test);
		g_fail_putchar = 1;
	}
	rewind(fptr);
	fclose(fptr);
	return (0);
}

int	putchar_cmp(int test_count)
{
	int	fd;

	fclose(fopen("libft_tests/putchar_ft.txt", "w"));
	fd = open("libft_tests/putchar_ft.txt", O_RDWR);
	ft_putchar_fd(g_tests[test_count], fd);
	close(fd);
	compare_files(test_count, g_tests[test_count]);
	return (test_count + 1);
}

int	putchar_test(int test_count, char *fail_flag)
{
	if (fail_flag)
		return (FINISH);
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	putchar_cmp(test_count);
	return (g_fail_putchar);
}
