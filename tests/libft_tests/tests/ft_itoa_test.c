/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:47:38 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 09:04:40 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <limits.h>

int							g_fail_itoa = 0;

typedef struct s_itoa_test
{
	size_t		test;
	char	*test_case;
}	t_itoa_test;

static const t_itoa_test	g_tests[] = {
[0] = {0, "0"},
[1] = {1, "1"},
[2] = {12, "12"},
[3] = {123, "123"},
[4] = {1234, "1234"},
[5] = {12345, "12345"},
[6] = {-123456, "-123456"},
[7] = {INT_MAX, "2147483647"},
[8] = {INT_MIN, "-2147483648"},
[9] = {2147483649, "-2147483647"},
[10] = {-2147483649, "2147483647"},
};


void	itoa_fork(int test_count, pid_t *child, void **shmem, \
char *(*f)(int n))
{
	char	*ret;
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = f(g_tests[test_count].test);
		memmove(*shmem, ret, strlen(ret));
		exit(0);
	}
}

int	itoa_cmp(int test_count, void **ft_shmem)
{
	pid_t	childs[2];
	char	*mem_test;

	itoa_fork(test_count, &childs[0], ft_shmem, &ft_itoa);
	if (wait_child(childs[0]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = ft_itoa(g_tests[test_count].test);
	free(mem_test);
	if (strcmp(g_tests[test_count].test_case, (char*)*ft_shmem))
	{
		g_fail_itoa += ft_log_str(test_count, g_tests[test_count].test_case, (char*)*ft_shmem);
		dprintf(2, "tcase: [1] %ld [2] %s\n", g_tests[test_count].test, \
		g_tests[test_count].test_case);
	}
	return (0);
}

int	itoa_test(int test_count, char *fail_flag)
{
	void	*ft_shmem;

	if (fail_flag != NULL)
		return (FINISH);
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	itoa_cmp(test_count, &ft_shmem);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_itoa);
}
