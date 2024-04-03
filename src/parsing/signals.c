/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:52:08 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/03 17:52:34 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_signal(int signal)
{
	static int	handling;
	char		*buf;

	handling = 0;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	if (signal == SIGINT)
    {
		handling = 1;
		buf = ft_strjoin("\n", buf);
		buf = ft_strjoin(buf, "$> ");
        write(1, buf, ft_strlen(buf));
		rl_redisplay();
		handling = 0;
    }
}

void	handle_key_combos(void)
{
	struct sigaction	sa_ctrl_c;

	sa_ctrl_c.sa_handler = &handle_signal;
	sa_ctrl_c.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_ctrl_c, NULL);
	signal(SIGQUIT, SIG_IGN);
}