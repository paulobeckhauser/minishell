/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/26 18:06:46 by sfrankie         ###   ########.fr       */
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
	char *color_prompt = ft_strjoin("\001\033[1;32m\002", prompt->buf);
	// char *color_prompt = ft_strjoin(prompt->buf, "$ ");
	color_prompt = ft_strjoin(color_prompt, "\001\033[0m\002");
	color_prompt = ft_strjoin(color_prompt, "$> ");
	// prompt->buf = ft_strjoin(prompt->buf, "$ ");
	// prompt->msg = readline(prompt->buf);
	prompt->msg = readline(color_prompt);
	add_history(prompt->msg);
}

int	count_quotes(t_prompt *prompt)
{
	int		i;
	char	start_quote;

	i = 0;
	start_quote = 0;
	while (prompt->msg[i])
	{
		if (prompt->msg[i] == '"' || prompt->msg[i] == '\'')
		{
			start_quote = prompt->msg[i];
			i++;
			break ;
		}
		i++;
	}
	while (prompt->msg[i])
	{
		if (prompt->msg[i] == start_quote)
			i++;
	}
	return (i);
}
