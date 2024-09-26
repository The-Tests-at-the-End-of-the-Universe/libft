/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 15:07:08 by spenning      #+#    #+#                 */
/*   Updated: 2024/08/28 12:51:55 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft_tester.h>

int wait_child(int pid)
{
	int got_pid;
	int status;

	got_pid = waitpid(pid, &status, 0);
	if ((got_pid == -1) && (errno != EINTR))
	{
		perror("waitpid");
		exit(1);
	}
	else if (WIFSIGNALED(status))	/* child exited on a signal */
		return (1);
	return (0);
}
