/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 17:08:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:53 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>
#include <fcntl.h>

int	g_fail_putendl = 0;

int	comparefile_putend(FILE *fPtr1, char *test, int *line, int *col)
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

int	compare_files_endl(int test_count, char *test)
{
	int		line;
	int		col;
	FILE	*fptr;
	char	*testnl;

	fptr = fopen("libft_tests/putendl_ft.txt", "r");
	if (fptr == NULL)
	{
		printf("\nUnable to open file.\n");
		return (-1);
	}
	testnl = calloc(strlen(test) + 2, 1);
	strncpy(testnl, test, strlen(test));
	testnl[strlen(test) + 1] = '\0';
	testnl[strlen(test)] = '\n';
	if (comparefile_putend(fptr, testnl, &line, &col) != 0)
	{
		g_fail_putendl += ft_log_int(test_count, line, col);
		dprintf(2, "tcase: %s\n", test);
	}
	rewind(fptr);
	fclose(fptr);
	free(testnl);
	return (0);
}

int	putendl_cmp(int test_count, char *test)
{
	int	fd;

	fclose(fopen("libft_tests/putendl_ft.txt", "w"));
	fd = open("libft_tests/putendl_ft.txt", O_RDWR);
	ft_putendl_fd(test, fd);
	close(fd);
	compare_files_endl(test_count, test);
	if (g_fail_putendl == 0)
		printf(GRN "%d OK " RESET, test_count);
	return (test_count + 1);
}

int	putendl_test(void)
{
	int	test_count;

	test_count = 1;
	test_count = putendl_cmp(test_count, "a");
	test_count = putendl_cmp(test_count, "b");
	test_count = putendl_cmp(test_count, "\200");
	test_count = putendl_cmp(test_count, "\n");
	test_count = putendl_cmp(test_count, "%");
	test_count = putendl_cmp(test_count, " ");
	test_count = putendl_cmp(test_count, "_");
	test_count = putendl_cmp(test_count, "safds_");
	return (g_fail_putendl);
}
