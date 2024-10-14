/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:07:08 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 08:58:46 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int						g_fail_memmove = 0;

typedef struct s_memmove_test
{
	char	*test;
	char	*test2;
	int		n;
}	t_memmove_test;

char * g_string = {"helloooo"};

static t_memmove_test	g_tests[] = {
[0] = {"fnjkdvbs", "fnjkdvbs", 5},
[1] = {"    scnaocuw9/", "    scnaocuw9/", 10},
[2] = {"snsicnsk sjknsjanc", "snsicnsk sjknsjanc", 10},
[3] = {"fnjkdvbs\n", "fnjkdvbs\n", 8},
[4] = {"NULL", "NULL", 0},
[5] = {"NULL", "NULL", 0},
[6] = {"BULL", "NULL", 4},
[7] = {"NULL", "BULL", 4},
[8] = {"NULK", "NULL", 4},
[9] = {"NULLLLLLLLL", "NULL", 11},
[10] = {"NULLLLLLLLLLLLLLLLLLL\
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", "NULLLLLLLLLLLLLLLLLLL\
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\
LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 128},
};

static const t_memmove_test	g_ftests[] = {
[0] = {"", 0, 0},
[1] = {NULL, "NULL", 1},
[2] = {"NULL", NULL, 1},
[3] = {NULL, NULL, 0},
[4] = {"NULL", "NULL", -100},
[5] = {"NULL", "NULL", 100},
[6] = {"NULLLL", "", 10},
};

void	memmove_fork(int test_count, pid_t *child, void **shmem, \
void *(*f)(void *, const void *, size_t n))
{
	char	*ret;
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = strdup(g_tests[test_count].test);
		f(ret, g_tests[test_count].test2, g_tests[test_count].n);
		memmove(*shmem, ret, strlen(ret));
		exit(0);
	}
}

int	memmove_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];
	char	*mem_test;

	memmove_fork(test_count, &childs[0], org_shmem, &memmove);
	memmove_fork(test_count, &childs[1], ft_shmem, &ft_memmove);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = strdup(g_tests[test_count].test); 
	ft_memmove(mem_test, g_tests[test_count].test2, g_tests[test_count].n);
	free(mem_test);
	if (strcmp((char*)*org_shmem, (char*)*ft_shmem))
	{
		g_fail_memmove += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [1] %s [2] %s [n] %d\n", g_tests[test_count].test, \
		g_tests[test_count].test2, g_tests[test_count].n);
	}
	return (0);
}

int	memmove_test(int test_count, char *fail_flag)
{
	void	*org_shmem;
	void	*ft_shmem;

	if (fail_flag)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (test_count == 6)
			g_tests[test_count].test2 = g_tests[test_count].test + 1;
		if (!strcmp("-ft", fail_flag))
			(void)ft_memmove(g_ftests[test_count].test, g_ftests[test_count].test2, g_ftests[test_count].n);
		if (!strcmp("-og", fail_flag))
			(void)memmove(g_ftests[test_count].test, g_ftests[test_count].test2, g_ftests[test_count].n); 
		return (g_fail_memmove);
	}
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	ft_shmem = create_shared_memory(sizeof(g_tests[test_count].test));
	memmove_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	if (munmap(ft_shmem, sizeof(g_tests[test_count].test)))
		exit(1);
	return (g_fail_memmove);
}
