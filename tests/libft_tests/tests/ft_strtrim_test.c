/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:51:07 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 09:03:07 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int	g_fail_strtrim = 0;

typedef struct s_strtrim_test
{
	char	*s1;
	char	*s2;
	char	*result;
}	t_strtrim_test;

static t_strtrim_test	g_tests[] = {
[0] = {"", "", ""},
[1] = {"aaaaaabaaaaaa", "a", "b"},
[2] = {"bobobbocobedbobobbo!", "!", "bobobbocobedbobobbo"},
[3] = {"a", "b", "a"},
[4] = {"aaaaaabbbbcbbbbaaaaaa", "ab", "c"},
};

void	strtrim_fork(int test_count, pid_t *child, void **shmem, \
char *(*f)(const char *, const char *))
{
	char *res;

	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		res = f(g_tests[test_count].s1, g_tests[test_count].s2);
		memmove(*shmem, res, strlen(res));
		exit(0);
	}
}

int	strtrim_cmp(int test_count, void **ft_shmem)
{
	pid_t	childs[1];
	char	*test;

	strtrim_fork(test_count, &childs[0], ft_shmem, &ft_strtrim);
	if (wait_child(childs[0]))
		return (printf(RED " SEGFAULT  "RESET));
	test = ft_strtrim(g_tests[test_count].s1, g_tests[test_count].s2);
	free(test);
	if (strcmp(g_tests[test_count].result, (char*)*ft_shmem))
	{
		g_fail_strtrim += ft_log_str(test_count, g_tests[test_count].result, (char*)*ft_shmem);
		dprintf(2, "tcase: [s1] %s [s2] %s [result] %s\n", g_tests[test_count].s1, \
		g_tests[test_count].s2, g_tests[test_count].result);
		g_fail_strtrim = 1;
	}
	return (0);
}

int	strtrim_test(int test_count)
{
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].result));
	if (strtrim_cmp(test_count, &ft_shmem))
		g_fail_strtrim = 1;
	if (munmap(ft_shmem, sizeof(g_tests[test_count].result)))
		exit(1);
	return (g_fail_strtrim);
}

