/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:06:45 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:51:07 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: handle_execution
 * --------------------------
 * Handles the SIGINT signal (Ctrl+C) during command execution.
 * 
 * signal: The signal number.
 * 
 * If the signal is SIGINT, it writes a newline character to standard output.
 */
void	handle_execution(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
	}
}

/* Function: handle_key_combos_execution
 * -------------------------------------
 * Sets up signal handling for specific key combinations during command execution.
 * 
 * This function configures the handling of the SIGINT signal (Ctrl+C) by setting up
 * a sigaction structure and using sigaction() to associate the signal with the
 * handle_execution function. It also ignores the SIGUSR1 signal.
 */
void	handle_key_combos_execution(void)
{
	struct sigaction	sa_ctrl_c;

	sa_ctrl_c.sa_handler = &handle_execution;
	sa_ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&sa_ctrl_c.sa_mask);
	sigaction(SIGINT, &sa_ctrl_c, NULL);
	signal(SIGUSR1, SIG_IGN);
}