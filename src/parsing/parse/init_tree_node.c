/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:31:35 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/21 12:46:02 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	join_redirection_to_cmd(t_token_node **token)
{
	if (!join_left_redirections_to_cmd(token))
		join_right_redirections_to_cmd(token);
}

int	join_left_redirections_to_cmd(t_token_node **token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD))
	{
		if ((*token)->prev && (*token)->prev->token.type == REDIRECTION)
		{
			if ((*token)->prev->prev
				&& (*token)->prev->prev->token.type == REDIRECTION)
			{
				(*token)->left = (*token)->prev->prev;
				(*token)->right = (*token)->prev;
				return (1);
			}
			else
			{
				(*token)->left = (*token)->prev;
				(*token)->right = NULL;
				return (0);
			}
		}
	}
	return (0);
}

void	join_right_redirections_to_cmd(t_token_node **token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD))
	{
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			if ((*token)->next->next && (*token)->next->next->token.type == REDIRECTION)
			{
				(*token)->left = (*token)->next;
				(*token)->right = (*token)->next->next;
				return ;
			}
			else
			{
				if (!(*token)->left)
					(*token)->left = (*token)->next;
				else
					(*token)->right = (*token)->next;
			}
		}
	}
}


void	join_tokens_to_pipe(t_token_node **token, t_token_node **first_pipe)
{
	join_left_token_to_pipe(token, first_pipe);
	join_right_token_to_pipe(token);
}

void	join_left_token_to_pipe(t_token_node **token, t_token_node **first_pipe)
{
	if ((*token)->prev && ((*token)->prev->token.type == BUILTIN_CMD
		|| (*token)->prev->token.type == SIMPLE_CMD))
	{
		if (!*first_pipe)
		{
			*first_pipe = *token;
			(*token)->left = (*token)->prev;
		}
		else
		{
			if ((*token)->prev->prev && (*token)->prev->prev->token.type == PIPE)
				(*token)->left = (*token)->prev->prev;
		}
	}
}

void	join_right_token_to_pipe(t_token_node **token)
{
	if ((*token)->next && ((*token)->next->token.type == BUILTIN_CMD
		|| (*token)->next->token.type == SIMPLE_CMD))
		(*token)->right = (*token)->next;
}
