/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/29 17:49:26 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>

int	g_fail_atoi = 0;

static const char * const tests[] = {
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
	[DONE] = "",
};

int	atoi_cmp(int test_count)
{
	int		result_org;
	int		result_ft;

	result_org = atoi(tests[test_count]);
	result_ft = ft_atoi(tests[test_count]);
	if (result_org != result_ft)
	{
		g_fail_atoi += ft_log_int(test_count, result_org, result_ft);
		dprintf(2, "tcase: %s\n", tests[test_count]);
		g_fail_atoi = 1;
	}
	else 
		g_fail_atoi = 0;
	return (g_fail_atoi);
}

int	atoi_test(int test_count)
{
	if (test_count == DONE)
		return (FINISH);
	atoi_cmp(test_count);
	return (g_fail_atoi);
}
