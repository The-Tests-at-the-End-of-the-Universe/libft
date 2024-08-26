/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:21:40 by spenning          #+#    #+#             */
/*   Updated: 2024/05/16 13:54:45 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_tester.h"

int	ft_log_chr(int test_count, FILE *errorlog, char ro, char rft)
{
	printf(RED "%d FAIL "RESET, test_count);
	fprintf(errorlog, "error\n");
	fprintf(errorlog, "test number: %d\n", test_count);
	fprintf(errorlog, "org: %c\n", ro);
	fprintf(errorlog, "ft: %c\n", rft);
	fprintf(errorlog, "---------\n");
	return (1);
}

int	ft_log_str(int test_count, FILE *errorlog, char *ro, char *rft)
{
	printf(RED "%d FAIL "RESET, test_count);
	fprintf(errorlog, "error\n");
	fprintf(errorlog, "test number: %d\n", test_count);
	fprintf(errorlog, "org: %s\n", ro);
	fprintf(errorlog, "ft: %s\n", rft);
	fprintf(errorlog, "---------\n");
	return (1);
}

int	ft_log_int(int test_count, FILE *errorlog, int result_org, int result_ft)
{
	printf(RED "%d FAIL "RESET, test_count);
	fprintf(errorlog, "error\n");
	fprintf(errorlog, "test number: %d\n", test_count);
	fprintf(errorlog, "org: %d\n", result_org);
	fprintf(errorlog, "ft: %d\n", result_ft);
	fprintf(errorlog, "---------\n");
	return (1);
}
