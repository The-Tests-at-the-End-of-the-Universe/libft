/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_test.c                                  :+:    :+:            */
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

int							g_fail_putstr = 0;
static int					g_fd = 0;
static char					*g_tests[] = {
[0] = "a",
[1] = "b",
[2] = "\200",
[3] = "\n",
[4] = "%",
[5] = NULL,
[6] = " ",
[7] = "_",
};

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
	char	*testnl;

	fptr = fopen("libft_tests/putstr_ft.txt", "r");
	if (fptr == NULL)
	{
		printf("\nUnable to open file.\n");
		return (-1);
	}
	testnl = calloc(strlen(test) + 2, 1);
	strncpy(testnl, test, strlen(test));
	testnl[strlen(test) + 1] = '\0';
	testnl[strlen(test)] = '\n';
	if (comparefile_putstr(fptr, testnl, &line, &col) != 0)
	{
		g_fail_putstr += ft_log_int(test_count, line, col);
		dprintf(2, "tcase: %s\n", test);
		g_fail_putstr = 1;
	}
	rewind(fptr);
	fclose(fptr);
	free(testnl);
	return (0);
}

void	putstr_fork(int test_count, pid_t *child, int (*f)(char *, int))
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		f(g_tests[test_count], g_fd);
		exit(0);
	}
}

int	putstr_cmp(int test_count)
{
	pid_t	childs[1];

	fclose(fopen("libft_tests/putstr_ft.txt", "w"));
	g_fd = open("libft_tests/putstr_ft.txt", O_RDWR);
	putstr_fork(test_count, &childs[0], &ft_putstr_fd);
	if (wait_child(childs[0]) && g_tests[test_count] != NULL)
		return (printf(RED " SEGFAULT "RESET));
	close(g_fd);
	if (g_tests[test_count] != NULL)
		compare_files_str(test_count, g_tests[test_count]);
	return (0);
}

int	putstr_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	putstr_cmp(test_count);
	return (g_fail_putstr);
}
