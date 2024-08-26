/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_log_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 11:21:40 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/26 15:56:35 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"

int	ft_log_chr(int test_count, char og, char ft)
{
	printf(RED "%d FAIL "RESET, test_count);
	dprintf(2, "[%d]\n", test_count);
	dprintf(2, "libOG: %c\n", og);
	dprintf(2, "libft: %c\n", ft);
	return (1);
}

int	ft_log_str(int test_count, char *og, char *ft)
{
	printf(RED "%d FAIL "RESET, test_count);
	dprintf(2, "[%d]\n", test_count);
	dprintf(2, "libOG: %s\n", og);
	dprintf(2, "libft: %s\n", ft);
	return (1);
}

int	ft_log_int(int test_count, int og, int ft)
{
	printf(RED "%d FAIL "RESET, test_count);
	dprintf(2, "[%d]\n", test_count);
	dprintf(2, "libOG: %d\n", og);
	dprintf(2, "libft: %d\n", ft);
	return (1);
}
