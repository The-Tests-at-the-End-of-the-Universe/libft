/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:12:54 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/06 15:49:46 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>
#include <string.h>

int							g_fail_calloc = 0;

typedef struct s_calloc_test
{
	size_t	nmemb;
	size_t	n;
}	t_calloc_test;

static const t_calloc_test	g_tests[] = {
[ZERO] = {1, sizeof(char)},
[ONE] = {1000, sizeof(char)},
[TWO] = {1000000, sizeof(char)},
[THREE] = {1, sizeof(int)},
[FOUR] = {1000, sizeof(int)},
[FIVE] = {1000000, sizeof(int)},
[SIX] = {1, sizeof(float)},
[SEVEN] = {1000, sizeof(float)},
[EIGHT] = {1000000, sizeof(float)},
[NINE] = {1, sizeof(void)},
[TEN] = {1000, sizeof(void)},
[ELEVEN] = {1000000, sizeof(void)},
[TWELVE] = {1, 1},
[THIRTEEN] = {5, 1},
[FOURTEEN] = {1, 5},
};


void	calloc_fork(int test_count, pid_t *child, void **shmem, \
void *(*f)(size_t nmemb, size_t n))
{
	char	*ret;

	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		ret = f(g_tests[test_count].n, g_tests[test_count].nmemb);
		memcpy(*shmem, ret, g_tests[test_count].n * g_tests[test_count].nmemb);
		exit(0);
	}
}

int	calloc_cmp(int test_count, void **org_shmem, void **ft_shmem)
{
	pid_t	childs[2];
	char	*mem_test;

	calloc_fork(test_count, &childs[0], org_shmem, &calloc);
	calloc_fork(test_count, &childs[1], ft_shmem, &ft_calloc);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	mem_test = ft_calloc(g_tests[test_count].n, g_tests[test_count].nmemb);
	free(mem_test);
	if (chrcmp((char*)*org_shmem, (char*)*ft_shmem, g_tests[test_count].n * g_tests[test_count].nmemb))
	{
		g_fail_calloc += ft_log_str(test_count, (char*)*org_shmem, (char*)*ft_shmem);
		dprintf(2, "tcase: [n] %ld [nmem] %ld\n", g_tests[test_count].n, \
		g_tests[test_count].nmemb);
	}
	return (0);
}

int	calloc_test(int test_count)
{
	void	*org_shmem;
	void	*ft_shmem;
	size_t	size;

	size = g_tests[test_count].n * g_tests[test_count].nmemb;
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	org_shmem = create_shared_memory(size);
	ft_shmem = create_shared_memory(size);
	calloc_cmp(test_count, &org_shmem, &ft_shmem);
	if (munmap(org_shmem, size))
		exit(1);
	if (munmap(ft_shmem, size))
		exit(1);
	return (g_fail_calloc);
}