/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/05 18:06:26 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Display current directory + prompt for user + addhistory for previous
// prompts
void default_display_with_history(t_prompt *prompt)
{
	prompt->buf = getcwd(NULL, 0);
	if (prompt->buf == NULL)
	{
		perror("getcwd() error");	
		return ;
	}
	char *color_prompt = ft_strjoin("\001\033[1;32m\002", prompt->buf);
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

void	check_quotes(t_prompt *prompt)
{
	while (count_quotes(prompt) % 2 != 0)
	{
		prompt->msg = ft_strjoin(prompt->msg, "\n");
		prompt->msg = ft_strjoin(prompt->msg, readline("> "));
	}
}

int	count_quotes(t_prompt *prompt)
{
	int		i;
	int		count;
	char	start_quote;

	i = 0;
	count = 0;
	start_quote = 0;
	while (prompt->msg[i])
	{
		if (prompt->msg[i] == '"' || prompt->msg[i] == '\'')
		{
			start_quote = prompt->msg[i];
			i++;
			count++;
			break ;
		}
		i++;
	}
	while (prompt->msg[i])
	{
		if (prompt->msg[i] == start_quote)
			count++;
		i++;
	}
	return (count);
}
