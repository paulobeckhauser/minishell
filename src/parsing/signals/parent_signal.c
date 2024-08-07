/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:52:08 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:29:47 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: handle_signal_parent
 * -------------------------------
 * Handles signals received by the parent process.
 * 
 * signal: The signal number received.
 * 
 * This function defines how the parent process reacts to SIGINT (Ctrl+C) signals.
 * If the global signal flag (g_signal) is not set, it writes a newline to standard
 * output, prepares readline to handle a new line, clears the current readline
 * buffer, and forces readline to redisplay the prompt with an empty buffer.
 */
void	handle_signal_parent(int signal)
{
	if (signal == SIGINT && !g_signal)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* Function: handle_parent_key_combos
 * -----------------------------------
 * Sets up signal handling for the parent process.
 * 
 * This function configures how the parent process should handle SIGINT (Ctrl+C)
 * and SIGQUIT (Ctrl+\) signals using the sigaction structure and function. It
 * ignores SIGQUIT and SIGUSR1 signals. The SA_RESTART flag is set to make certain
 * system calls restartable across signals.
 */
void	handle_parent_key_combos(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal_parent;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
}