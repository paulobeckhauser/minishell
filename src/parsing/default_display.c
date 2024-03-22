/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/21 23:13:29 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Display current directory + prompt for user + addhistory for previous
// prompts
void	default_display_with_history(t_prompt *prompt)
{
	prompt->buf = getcwd(NULL, 0);
	if (prompt->buf == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	prompt->buf = ft_strjoin(prompt->buf, "$ ");
	prompt->msg = readline(prompt->buf);
	add_history(prompt->msg);
}