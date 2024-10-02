/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri_test.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:52:33 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/02 13:07:38 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_striteri = 0;

typedef struct s_striteri_test
{
	char	*string;
	char	*result;
}	t_striteri_test;

static t_striteri_test	g_tests[] = {
[ZERO] = {"", ""},
[ONE] = {"123", "135"},
[TWO] = {"abc", "ace"},
[THREE] = {"ABC", "ACE"},
};

void	test_function(unsigned int c, char *s)
{
	s[0] = s[0] + c;
}

void	striteri_fork(int test_count, pid_t *child, void **shmem, \
void (*f)(char *, void (*)(unsigned int, char *)))
{
	char	*dup;

	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		dup = strdup(g_tests[test_count].string);
		f(dup, test_function);
		memmove(*shmem, dup, strlen(dup));
		exit(0);
	}
}

int	striteri_cmp(int test_count, void **ft_shmem)
{
	pid_t	childs[1];

	striteri_fork(test_count, &childs[0], ft_shmem, &ft_striteri);
	if (wait_child(childs[0]))
		return (printf(RED " MKO "RESET));
	if (strcmp(g_tests[test_count].result, (char*)*ft_shmem))
	{
		g_fail_striteri += ft_log_str(test_count, g_tests[test_count].result, *ft_shmem);
		dprintf(2, "tcase: [string] %s [result] %s\n", g_tests[test_count].string, \
		g_tests[test_count].result);
		g_fail_striteri = 1;
	}
	return (0);
}

int	striteri_test(int test_count)
{
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	striteri_cmp(test_count, &ft_shmem);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	return (g_fail_striteri);
}
