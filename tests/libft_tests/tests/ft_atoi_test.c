/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/14 09:47:02 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>

int							g_fail_atoi = 0;

static const char *const	g_tests[] = {
[0] = "",
[1] = "1",
[2] = "12",
[3] = "123",
[4] = "1234",
[5] = "  12345",
[6] = "  12345",
[7] = "123 456",
[8] = "A2143244535",
[9] = "2143244535",
[10] = "",
[11] = "asbj",
[12] = "asbj12345",
[13] = "       ",
[14] = "-00123",
[15] = "--00123",
[16] = "-+-+-00123",
[17] = "-+-+-00123",
[18] = "++00123",
[19] = "++--00123",
[20] = "  -00123",
[21] = "		--00123",
[22] = "	 	 ---00123",
};

static const char *const	g_ftests[] = {
[0] = "",
[1] = NULL,
[2] = "3472357958327572398758",
};

void	atoi_fork(int test_count, pid_t *child, int (*f)(const char *))
{
	*child = fork();
	if (*child == -1)
		exit(1);
	if (*child == 0)
	{
		f(g_tests[test_count]);
		exit(0);
	}
}

int	atoi_cmp(int test_count)
{
	pid_t	childs[2];
	int		ft;
	int		org;

	atoi_fork(test_count, &childs[0], &atoi);
	atoi_fork(test_count, &childs[1], &ft_atoi);
	if (wait_child(childs[0]) != wait_child(childs[1]))
		return (printf(RED " SEGFAULT "RESET));
	ft_atoi(g_tests[test_count]); 
	ft = ft_atoi(g_tests[test_count]);
	org = atoi(g_tests[test_count]);
	if (ft != org)
	{
		g_fail_atoi += ft_log_int(test_count, org, ft);
		dprintf(2, "tcase: [1] %s\n", g_tests[test_count]);
	}
	return (0);
}

int	atoi_test(int test_count, char	*fail_flag)
{
	int test;

	if (fail_flag != NULL)
	{
		if (test_count == sizeof(g_ftests) / sizeof(g_ftests[0]))
			return (FINISH);	
		if (!strcmp("-ft", fail_flag))
			test = ft_atoi(g_ftests[test_count]); 
		if (!strcmp("-og", fail_flag))
			test = atoi(g_ftests[test_count]);
		(void)test; 
		return (g_fail_atoi);
	}
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	atoi_cmp(test_count);
	return (g_fail_atoi);
}
