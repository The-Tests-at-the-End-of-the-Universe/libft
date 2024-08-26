/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 06:01:09 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/08/26 14:53:04 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"
#include <bsd/string.h>

int	g_fail_strlcat = 0;

int	ift(char *output, char *test, char *test2, size_t n)
{
	char	*test2_dub;
	size_t	ret;

	output = strdup(test);
	test2_dub = strdup(test2);
	if (output == NULL || test2_dub == NULL)
	{
		if (output)
			free(output);
		if (test2_dub)
			free(test2_dub);
		printf("Error with initft\n");
		return (0);
	}
	ret = ft_strlcat(output, test2_dub, n);
	free(test2_dub);
	return (ret);
}

int	iorg(char *output, char *test, char *test2, size_t n)
{
	char	*test2_dub;
	size_t	ret;

	output = strdup(test);
	test2_dub = strdup(test2);
	if (output == NULL || test2_dub == NULL)
	{
		if (output)
			free(output);
		if (test2_dub)
			free(test2_dub);
		printf("Error with initft\n");
		return (0);
	}
	ret = strlcat(output, test2_dub, n);
	free(test2_dub);
	return (ret);
}

int	strlcat_cmp(int test_count, char *t1, char *t2, size_t n)
{
	FILE	*errorlog;
	char	*org;
	char	*ft;

	org = NULL;
	ft = NULL;
	errorlog = fopen("logs/error_log.txt", "a");
	if (errorlog == NULL)
	{
		printf("Error opening log file\n");
		return (1);
	}
	if (ift(ft, t1, t2, n) != iorg(org, t1, t2, n) && strcmp(org, ft))
		g_fail_strlcat += ft_log_str(test_count, errorlog, org, ft);
	else
		printf(GRN "%d OK " RESET, test_count);
	free(org);
	free(ft);
	fclose(errorlog);
	return (test_count + 1);
}

int	strlcat_test(void)
{
	int	tc;

	tc = 1;
	tc = strlcat_cmp(tc, "nfdsnkjd", "dlksadbs", 16);
	tc = strlcat_cmp(tc, "bobobbocob", "dlksadbs", 18);
	tc = strlcat_cmp(tc, "a", "b", 2);
	tc = strlcat_cmp(tc, "dfsfdsf?", "??cbdscds", 17);
	tc = strlcat_cmp(tc, "", "", 0);
	tc = strlcat_cmp(tc, " ", " ", 2);
	return (g_fail_strlcat);
}
