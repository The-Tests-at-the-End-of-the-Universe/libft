/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:33:32 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/06 22:02:10 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_strmapi = 0;

typedef struct s_strmapi_test
{
	char	*string;
	char	*result;
}	t_strmapi_test;

static t_strmapi_test	g_tests[] = {
[ZERO] = {"", ""},
[ONE] = {"123", "135"},
[TWO] = {"abc", "ace"},
[THREE] = {"ABC", "ACE"},
};

char	test_function_mapi(unsigned int c, char s)
{
	char	r;

	r = s + c;
	return (r);
}

void	strmapi_fork(int test_count, pid_t *child, void **shmem, \
char * (*f)(const char *, char (*)(unsigned int, char)))
{
	char	*dup;

	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		dup = f(g_tests[test_count].string, test_function_mapi);
		memmove(*shmem, dup, strlen(dup));
		exit(0);
	}
}

int	strmapi_cmp(int test_count, void **ft_shmem)
{
	pid_t	childs[1];
	char	*mem_test;

	strmapi_fork(test_count, &childs[0], ft_shmem, &ft_strmapi);
	if (wait_child(childs[0]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = ft_strmapi(g_tests[test_count].string, test_function_mapi);
	free(mem_test);
	if (strcmp(g_tests[test_count].result, (char*)*ft_shmem))
	{
		g_fail_strmapi += ft_log_str(test_count, g_tests[test_count].result, *ft_shmem);
		dprintf(2, "tcase: [string] %s [result] %s\n", g_tests[test_count].string, \
		g_tests[test_count].result);
		g_fail_strmapi = 1;
	}
	return (0);
}

int	strmapi_test(int test_count)
{
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	if (strmapi_cmp(test_count, &ft_shmem))
		g_fail_strmapi = 1;
	if (munmap(ft_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	return (g_fail_strmapi);
}
