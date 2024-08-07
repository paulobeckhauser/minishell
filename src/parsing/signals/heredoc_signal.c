/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:24:44 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:29:24 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: handle_signal_heredoc
 * --------------------------------
 * Handles signals received during the execution of a heredoc.
 * 
 * signal: The signal number received.
 * 
 * This function defines how heredoc processes react to SIGINT (Ctrl+C) signals.
 * Upon receiving SIGINT, it writes a newline to standard output, attempts to open
 * a temporary file in write-only mode with truncation (effectively clearing it),
 * closes the file descriptor if the file was successfully opened, and then exits
 * the process with status 0.
 */
void	handle_signal_heredoc(int signal)
{
	int	fd;

	fd = 0;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		fd = open("tmp/heredoc_tmp", O_WRONLY | O_TRUNC);
		if (fd != -1)
			close(fd);
		exit(0);
	}
}

/* Function: handle_heredoc_key_combos
 * ------------------------------------
 * Sets up signal handling for heredoc processes.
 * 
 * This function configures how heredoc processes should handle SIGINT (Ctrl+C)
 * signals using the sigaction structure and function. It also ignores SIGQUIT
 * (Ctrl+\) and SIGUSR1 signals. The SA_RESTART flag is set to make certain system
 * calls restartable across signals.
 */
void	handle_heredoc_key_combos(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal_heredoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
}