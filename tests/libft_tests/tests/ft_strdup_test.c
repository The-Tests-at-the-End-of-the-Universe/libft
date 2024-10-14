/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 05:44:11 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/10/14 09:58:35 by mynodeus      ########   odam.nl         */
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
[0] = {""},
[1] = {"nfdsnkjdsnciudsbccknd?cbdscds"},
[2] = {"bobobbocobedbobobbobob!"},
[3] = {"dfsfdsf???cbdscds"},
[4] = {"sdncdskj nkjsanckjdsncj\ndkj"},
};

static const t_strdup_test	g_ftests[] = {
[0] = {""},
[1] = {NULL},
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
	char	*mem_test;

	strdup_fork(test_count, &childs[0], org_shmem, &strdup);
	strdup_fork(test_count, &childs[1], ft_shmem, &ft_strdup);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = ft_strdup(g_tests[test_count].string);
	free(mem_test);
	if (strcmp((char*)*org_shmem, (char*)*ft_shmem))
	{
		g_fail_strdup += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [string] %s\n", g_tests[test_count].string);
		g_fail_strdup = 1;
	}
	return (0);
}

int	strdup_test(int test_count, char *fail_flag)
{
	void	*org_shmem;
	void	*ft_shmem;

	if (fail_flag)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (!strcmp("-ft", fail_flag))
			org_shmem = ft_strdup(g_ftests[test_count].string);
		if (!strcmp("-og", fail_flag))
			org_shmem = strdup(g_ftests[test_count].string); 
		(void)org_shmem;
		return (g_fail_strdup);
	}
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].string));
	if (strdup_cmp(test_count, &org_shmem, &ft_shmem))
		g_fail_strdup = 1;
	if (munmap(org_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].string)))
		exit(1);
	return (g_fail_strdup);
}
