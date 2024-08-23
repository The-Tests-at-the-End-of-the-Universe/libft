/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:26:06 by spenning          #+#    #+#             */
/*   Updated: 2024/05/16 15:36:01 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <string.h>

int	g_fail_memset = 0;

char	*init_ft_memset(char *test, int c, size_t n)
{
	char	*test_dub;

	test_dub = strdup(test);
	if (test_dub == NULL)
		return (NULL);
	return (ft_memset(test_dub, c, n));
}

char	*init_org_memset(char *test, int c, size_t n)
{
	char	*test_dub;

	test_dub = strdup(test);
	if (test_dub == NULL)
		return (NULL);
	return (memset(test_dub, c, n));
}

int	memset_cmp(int test_count, char *test, int c, size_t n)
{
	FILE	*errorlog;
	char	*org;
	char	*ft;

	errorlog = fopen("logs/error_log.txt", "a");
	org = init_org_memset(test, c, n);
	ft = init_ft_memset(test, c, n);
	if (org == NULL || ft == NULL || errorlog == NULL)
	{
		if (org)
			free(org);
		if (ft)
			free(ft);
		printf("Error with allocation\n");
		return (1);
	}
	if (strcmp(org, ft))
		g_fail_memset += ft_log_str(test_count, errorlog, org, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	free(org);
	free(ft);
	fclose(errorlog);
	return (test_count + 1);
}

int	memset_test(void)
{
	int	test_count;

	test_count = 1;
	printf("\n");
	printf(BMAG "ft_memset\n" RESET);
	test_count = memset_cmp(test_count, "fnjkdvbs", 'c', 2);
	test_count = memset_cmp(test_count, "    scnaocuw9/", 'a', 10);
	test_count = memset_cmp(test_count, "fnjkdvbs", '\n', 4);
	test_count = memset_cmp(test_count, "snsicnsk sjknsjanc", 0, 10);
	test_count = memset_cmp(test_count, "fnjkdvbs\n", 255, 0);
	test_count = memset_cmp(test_count, "fnjkdvbs\n", 's', 2);
	test_count = memset_cmp(test_count, "fnjkdvb0", 's', 6);
	test_count = memset_cmp(test_count, "NULL", 0, 0);
	return (g_fail_memset);
}
