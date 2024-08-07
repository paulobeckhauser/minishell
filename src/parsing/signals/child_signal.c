/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:24:38 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:28:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: handle_signal_child
 * ------------------------------
 * Handles signals received by child processes.
 * 
 * signal: The signal number received.
 * 
 * This function defines how child processes react to SIGINT (Ctrl+C) and SIGQUIT
 * (Ctrl+\) signals. For SIGINT, it simply prints a newline. For SIGQUIT, it prints
 * "Quit (core dumped)" to standard error and replaces the current readline buffer
 * with an empty string, effectively ignoring the input.
 */
void	handle_signal_child(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		rl_replace_line("", 0);
	}
}

/* Function: handle_child_key_combos
 * ----------------------------------
 * Sets up signal handling for child processes.
 * 
 * This function configures how child processes should handle SIGINT (Ctrl+C) and
 * SIGQUIT (Ctrl+\) signals using the sigaction structure and function. It also
 * ignores SIGUSR1 signals. The SA_RESTART flag is set to make certain system calls
 * restartable across signals.
 */
void	handle_child_key_combos(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal_child;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGUSR1, SIG_IGN);
}