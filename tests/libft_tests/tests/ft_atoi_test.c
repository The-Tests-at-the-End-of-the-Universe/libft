/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/10/06 14:32:13 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>

int							g_fail_atoi = 0;

static const char *const	g_tests[] = {
[ZERO] = "",
[ONE] = "1",
[TWO] = "12",
[THREE] = "123",
[FOUR] = "1234",
[FIVE] = "  12345",
[SIX] = "  12345",
[SEVEN] = "123 456",
[EIGHT] = "A2143244535",
[NINE] = "2143244535",
[TEN] = "",
[ELEVEN] = "asbj",
[TWELVE] = "",
[THIRTEEN] = "       ",
[FOURTEEN] = "-00123",
[FIVETEEN] = "--00123",
[SIXTEEN] = "-+-+-00123",
[SEVENTEEN] = "-+-+-00123",
[EIGHTEEN] = "++00123",
[NINETEEN] = "++--00123",
[TWENTY] = "  -00123",
[TWENTYONE] = "		--00123",
[TWENTYTWO] = "	 	 ---00123",
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
// this test does not have memory test because it was too difficult to distinguish between
// normal memory issue compared with normal atoi versus abnormal mem issue
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

int	atoi_test(int test_count)
{
	if (test_count == sizeof(g_tests) / sizeof(g_tests[0]))
		return (FINISH);
	atoi_cmp(test_count);
	return (g_fail_atoi);
}
