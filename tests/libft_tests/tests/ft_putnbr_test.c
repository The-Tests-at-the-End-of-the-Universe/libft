/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 17:08:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 09:03:39 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>
#include <fcntl.h>

int			g_fail_putnbr = 0;

static int	g_tests[] = {
[0] = 0,
[1] = 1,
[2] = INT_MAX,
[3] = INT_MIN,
[4] = 1351546813,
[5] = -52454363,
[6] = 100,
[7] = 999,
};

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
			return (free(test), 0);
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

	fptr = fopen("libft_tests/putnbr_ft.txt", "r");
	if (fptr == NULL)
	{
		printf("\nUnable to open file.\n");
		return (-1);
	}
	if (comparefile_putnbr(fptr, ft_itoa(test), &line, &col) != 0)
	{
		g_fail_putnbr += ft_log_int(test_count, line, col);
		dprintf(2, "tcase: %d\n", test);
		g_fail_putnbr = 1;
	}
	rewind(fptr);
	fclose(fptr);
	return (0);
}

int	putnbr_cmp(int test_count)
{
	int	fd;

	fclose(fopen("libft_tests/putnbr_ft.txt", "w"));
	fd = open("libft_tests/putnbr_ft.txt", O_RDWR);
	ft_putnbr_fd(g_tests[test_count], fd);
	close(fd);
	compare_files_nbr(test_count, g_tests[test_count]);
	return (test_count + 1);
}

int	putnbr_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	putnbr_cmp(test_count);
	return (g_fail_putnbr);
}
