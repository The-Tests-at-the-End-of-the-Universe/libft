/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_tester_welcome.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/07 17:05:19 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tester.h"
#include <stdio.h>

void	welcome_screen_end(void)
{
	printf(CYN "<==========================================" RESET);
	printf(CYN "========================================>\n" RESET);
	printf(CYN "+                                          " RESET);
	printf(CYN "                                        +\n" RESET);
	printf(CYN "+                             " RESET);
	printf(YEL "    libft" RESET);
	printf(CYN " tester    " RESET);
	printf(CYN "                                 +\n" RESET);
	printf(CYN "+                                  by spenning" RESET);
	printf(CYN "                                     +\n" RESET);
	printf(CYN "+                                          " RESET);
	printf(CYN "                                        +\n" RESET);
	printf(CYN "<=============================================" RESET);
	printf(CYN "=====================================>\n" RESET);
}

void	welcome_screen_begin(void)
{
	printf(CYN "<==========================================" RESET);
	printf(CYN "========================================>\n" RESET);
	printf(CYN "||                                         " RESET);
	printf(CYN "                                       ||\n" RESET);
	printf(CYN "||    ||      |      ||  ||||||  ||     |||||" RESET);
	printf(CYN "   ||||||    |||| |||||   ||||||     ||\n" RESET);
	printf(CYN "||    ||     |||     ||  ||      ||    ||    " RESET);
	printf(CYN "  ||    ||  ||   ||   ||  ||         ||\n" RESET);
	printf(CYN "||    ||    || ||    ||  ||||||  ||    ||    " RESET);
	printf(CYN "  ||    ||  ||   ||   ||  ||||||     ||\n" RESET);
	printf(CYN "||     ||  ||   ||  ||   ||      ||    ||    " RESET);
	printf(CYN "  ||    ||  ||   ||   ||  ||         ||\n" RESET);
	printf(CYN "||      ||||     ||||    ||||||  |||||  |||||" RESET);
	printf(CYN "   ||||||   ||   ||   ||  ||||||     ||\n" RESET);
	printf(CYN "||                                           " RESET);
	printf(CYN "                                     ||\n" RESET);
}

int	main(void)
{
	welcome_screen_begin();
	welcome_screen_end();
	return (0);
}
