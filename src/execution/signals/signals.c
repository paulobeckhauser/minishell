/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:06:45 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/20 16:50:45 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	handle_execution(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
	}
}

void	handle_key_combos_execution(void)
{
	struct sigaction	sa_ctrl_c;

	sa_ctrl_c.sa_handler = &handle_execution;
	sa_ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&sa_ctrl_c.sa_mask);
	sigaction(SIGINT, &sa_ctrl_c, NULL);
	signal(SIGUSR1, SIG_IGN);
}
