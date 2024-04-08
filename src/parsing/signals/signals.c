/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:52:08 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/08 23:04:47 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	handle_signal(int signal)
{
	if (signal == SIGINT && g_signal == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_key_combos(void)
{
	struct sigaction	sa_ctrl_c;

	sa_ctrl_c.sa_handler = &handle_signal;
	sa_ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&sa_ctrl_c.sa_mask);
	sigaction(SIGINT, &sa_ctrl_c, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal_heredoc(int signal)
{
	if (signal == SIGINT && g_signal == 1)
	{
		write(1, "\n", 1);
		exit(0);
	}
}

void	handle_heredoc_combos(void)
{
	struct sigaction	sa_ctrl_c;

	sa_ctrl_c.sa_handler = &handle_signal_heredoc;
	sa_ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&sa_ctrl_c.sa_mask);
	sigaction(SIGINT, &sa_ctrl_c, NULL);
	signal(SIGQUIT, SIG_IGN);
}
