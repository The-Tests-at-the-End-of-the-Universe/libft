/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:44:11 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/09/29 22:01:42 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_strdup = 0;

typedef struct s_strdup_test
{
	char	*string;
}	t_strdup_test;

static t_strdup_test	g_tests[] = {
[ZERO] = {""},
[ONE] = {"nfdsnkjdsnciudsbccknd?cbdscds"},
[TWO] = {"bobobbocobedbobobbobob!"},
[THREE] = {"dfsfdsf???cbdscds"},
[FOUR] = {"sdncdskj nkjsanckjdsncj\ndkj"},
};

void	strdup_fork(int test_count, pid_t *child, void **shmem, \
char *(*f)(const char *))
{
	char	*ret;
	
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = f(g_tests[test_count].string);
		memmove(shmem, ret, strlen(ret));
		exit(0);
	}
}

int	strdup_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];

	strdup_fork(test_count, &childs[0], org_shmem, &strdup);
	strdup_fork(test_count, &childs[1], ft_shmem, &ft_strdup);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " MKO "RESET));
	if (strcmp(*org_shmem, *ft_shmem))
	{
		g_fail_strdup += ft_log_str(test_count, *org_shmem, *ft_shmem);
		dprintf(2, "tcase: [string] %s\n", g_tests[test_count].string);
		g_fail_strdup = 1;
	}
	return (0);
}

int	strdup_test(int test_count)
{
	void	*org_shmem;
	void	*ft_shmem;

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	strdup_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	return (g_fail_strdup);
}
