/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:27:38 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 09:03:07 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <bsd/string.h>

int					g_fail_strrchr = 0;

typedef struct s_strrchr_test
{
	char	*string;
	char	delim;
}	t_strrchr_test;

static t_strrchr_test	g_tests[] = {
[0] = {"", 0},
[1] = {"nfdsnkjdsnciudsbccknd?cbdscds", '?'},
[2] = {"bobobbocobedbobobbobob!", '!'},
[3] = {"dfsfdsf???cbdscds", '?'},
[4] = {"sdncdskj nkjsanckjdsncj\ndkj", '\n'},
};

void	strrchr_fork(int test_count, pid_t *child, char **shmem, \
char *(*f)(const char *, int))
{
	char	*ret;
	
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = f(g_tests[test_count].string, g_tests[test_count].delim);
		memmove(*shmem, ret, strlen(ret));
		exit(0);
	}
}

int	strrchr_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];
	char	*test;

	strrchr_fork(test_count, &childs[0], (char**)org_shmem, &strrchr);
	strrchr_fork(test_count, &childs[1], (char**)ft_shmem, &ft_strrchr);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT  "RESET));
	test = ft_strrchr(g_tests[test_count].string, g_tests[test_count].delim);
	(void)test;
	if (strcmp((char*)*org_shmem, (char*)*ft_shmem))
	{
		g_fail_strrchr += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [string] %s [delim] %c\n", g_tests[test_count].string, \
		g_tests[test_count].delim);
		g_fail_strrchr = 1;
	}
	return (0);
}

int	strrchr_test(int test_count)
{
	void	*org_shmem;
	void	*ft_shmem;
	

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	if (strrchr_cmp(test_count, &org_shmem, &ft_shmem))
		g_fail_strrchr = 1;
	if (munmap(org_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	return (g_fail_strrchr);
}

