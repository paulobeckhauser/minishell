/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:24:44 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 10:32:43 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	handle_signal_heredoc(int signal)
{
	if (signal == SIGINT && g_signal == 1)
	{
		write(1, "\n", 1);
		exit(0);
	}
}

void	handle_heredoc_key_combos(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal_heredoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
