/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:12:56 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/22 16:32:41 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	mark_last_redirection(t_token)

void	delete_repeating_redirection_tokens(t_token_node **tokens)
{
	t_token_node	*head;
	t_token_node	*tmp;

	while ((*tokens)->token.type == REDIRECTION && (*tokens)->next
		&& (*tokens)->next->token.type == REDIRECTION
		&& (*tokens)->token.t_value.single_ptr[0]
		== (*tokens)->next->token.t_value.single_ptr[0])
	{
		close_token_fd(*tokens);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp);
	}
	head = *tokens;
	while (*tokens)
	{
		// if ((*tokens)->token.type == REDIRECTION)
		// {
		// 	while ((*tokens)->token.type == REDIRECTION && (*tokens)->next
		// 		&& (*tokens)->next->token.type == REDIRECTION
		// 		&& (*tokens)->token.t_value.single_ptr[0]
		// 		== (*tokens)->next->token.t_value.single_ptr[0])
		// 	{
		// 		close_token_fd(*tokens);
		// 		tmp = *tokens;
		// 		*tokens = (*tokens)->next;
		// 		free(tmp);
		// 	}
		// }
		// *tokens = (*tokens)->next;
		if ((*tokens)->next && (*tokens)->next->next && (*tokens)->next->token.type == REDIRECTION
			&& (*tokens)->next->next->token.type == REDIRECTION
			&& (*tokens)->next->token.t_value.single_ptr[0]
			== (*tokens)->next->next->token.t_value.single_ptr[0])
		{
			tmp = (*tokens)->next->next;
			close_token_fd((*tokens)->next);
			free((*tokens)->next);
			(*tokens)->next = tmp;
		}
		else
			*tokens = (*tokens)->next;
	}
	*tokens = head;
}

void	close_token_fd(t_token_node *tokens)
{
	if (tokens->token.in.file_name)
	{
		if (close(tokens->token.in.fd) == -1)
			perror("close");
	}
	else if (tokens->token.out.file_name)
	{
		if (close(tokens->token.out.fd) == -1)
			perror("close");
	}
}
