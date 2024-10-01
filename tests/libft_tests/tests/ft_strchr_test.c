/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:44:11 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/01 11:14:04 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int					g_fail_strchr = 0;

typedef struct s_strchr_test
{
	char	*string;
	char	delim;
}	t_strchr_test;

static t_strchr_test	g_tests[] = {
[ZERO] = {"", 0},
[ONE] = {"nfdsnkjdsnciudsbccknd?cbdscds", '?'},
[TWO] = {"bobobbocobedbobobbobob!", '!'},
[THREE] = {"dfsfdsf???cbdscds", '?'},
[FOUR] = {"sdncdskj nkjsanckjdsncj\ndkj", '\n'},
};

void	strchr_fork(int test_count, pid_t *child, char **shmem, \
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
		// printf("**adress %p\n", shmem);
		// printf("*adress %p\n", *shmem);
		// printf("in child %s\n", *shmem);
		exit(0);
	}
}

int	strchr_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];

	strchr_fork(test_count, &childs[0], (char**)org_shmem, &strchr);
	strchr_fork(test_count, &childs[1], (char**)ft_shmem, &ft_strchr);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " MKO "RESET));
	if (strcmp((char*)*org_shmem, (char*)*ft_shmem))
	{
		g_fail_strchr += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [string] %s [delim] %c\n", g_tests[test_count].string, \
		g_tests[test_count].delim);
		g_fail_strchr = 1;
	}
	return (0);
}

int	strchr_test(int test_count)
{
	void	*org_shmem;
	void	*ft_shmem;
	

	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	strchr_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	return (g_fail_strchr);
}
