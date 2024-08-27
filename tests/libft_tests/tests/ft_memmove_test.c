/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:07:08 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/27 16:00:58 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_memmove = 0;

char	*init_ft_mv(char *test, char *test2, size_t n)
{
	char	*test_dub;
	char	*test2_dub;
	char	*ret;

	test_dub = strdup(test);
	test2_dub = strdup(test2);
	if (test_dub == NULL || test2_dub == NULL)
	{
		if (test_dub)
			free(test_dub);
		if (test2_dub)
			free(test2_dub);
		printf("Error with initft\n");
		return (NULL);
	}
	ret = ft_memmove(test_dub, test2_dub, n);
	free(test2_dub);
	return (ret);
}

char	*init_org_mv(char *test, char *test2, size_t n)
{
	char	*test_dub;
	char	*test2_dub;
	char	*ret;

	test_dub = strdup(test);
	test2_dub = strdup(test2);
	if (test_dub == NULL || test2_dub == NULL)
	{
		if (test_dub)
			free(test_dub);
		if (test2_dub)
			free(test2_dub);
		printf("Error with init_org\n");
		return (NULL);
	}
	ret = memmove(test_dub, test2_dub, n);
	free(test2_dub);
	return (ret);
}

int	memmove_cmp(int test_count, char *test, char *test2, size_t n)
{
	char	*org;
	char	*ft;

	org = init_org_mv(test, test2, n);
	ft = init_ft_mv(test, test2, n);
	if (strcmp(org, ft))
	{
		g_fail_memmove += ft_log_str(test_count, org, ft);
		dprintf(2, "tcase: [1] %s [2] %s\n", test, test2);
	}
	else
		printf(GRN "%d OK " RESET, test_count);
	free(org);
	free(ft);
	return (test_count + 1);
}

int	memmove_test(void)
{
	int	tc;

	tc = 1;
	tc = memmove_cmp(tc, "fnjkdvbs", "scnaocuw9", 2);
	tc = memmove_cmp(tc, "    scnaocuw9/", "    scnaocuw9/", 10);
	tc = memmove_cmp(tc, "fnjkdvbs", "snsicnsk", 4);
	tc = memmove_cmp(tc, "snsicnsk sjknsjanc", "snsicnsk fnjkdvbs", 10);
	tc = memmove_cmp(tc, "fnjkdvbs\n", "fnjkdvbs\n", 0);
	tc = memmove_cmp(tc, "fnjkdvbs\n", "fnjkdvbs\n", 2);
	tc = memmove_cmp(tc, "fnjkdvb0", "fnjkdvb0", 6);
	tc = memmove_cmp(tc, "NULL", "NULL", 0);
	return (g_fail_memmove);
}
