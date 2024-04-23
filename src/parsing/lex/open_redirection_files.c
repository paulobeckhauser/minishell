/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection_files.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:25:20 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 22:38:56 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	open_redirection_files(t_token_node *tokens)
{
	while (tokens)
	{
		if (tokens->token.type == REDIRECTION && tokens->token.in.file_name)
		{
			if (!open_in_red_token(tokens))
				return (0);
		}
		else if (tokens->token.type == REDIRECTION
			&& tokens->token.out.file_name)
		{
			if (!open_out_red_token(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	open_in_red_token(t_token_node *tokens)
{
	int	i;

	if (tokens->token.in.file_name)
	{
		i = 0;
		while (tokens->token.in.file_name[i])
		{
			tokens->token.in.fd = open(tokens->token.in.file_name[i], O_RDONLY);
			if (tokens->token.in.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.in.file_name[i]);
				return (0);
			}
			if (close(tokens->token.in.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.in.file_name[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	open_out_red_token(t_token_node *tokens)
{
	int	i;

	if (tokens->token.out.file_name)
	{
		i = 0;
		while (tokens->token.out.file_name[i])
		{
			open_based_on_trunc(tokens, i);
			if (tokens->token.out.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.out.file_name[i]);
				return (0);
			}
			if (close(tokens->token.out.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.out.file_name[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void	open_based_on_trunc(t_token_node *tokens, int i)
{
	if (tokens->token.out.trunc[i])
		tokens->token.out.fd = open(tokens->token.out.file_name[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		tokens->token.out.fd = open(tokens->token.out.file_name[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}
