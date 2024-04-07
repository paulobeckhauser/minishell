/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/07 15:23:02 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Display current directory + prompt for user + addhistory for previous
// prompts
void	default_display_with_history(t_prompt *prompt)
{
	char	*color_prompt;

	prompt->buf = getcwd(NULL, 0);
	if (prompt->buf == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	color_prompt = ft_strjoin("\001\033[1;32m\002", prompt->buf);
	color_prompt = ft_strjoin(color_prompt, "\001\033[0m\002");
	color_prompt = ft_strjoin(color_prompt, "$> ");
	handle_key_combos();
	prompt->msg = readline(color_prompt);
	if (prompt->msg == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	check_quotes(prompt);
	add_history(prompt->msg);
}
