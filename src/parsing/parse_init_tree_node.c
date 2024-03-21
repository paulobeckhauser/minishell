/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_tree_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:47:52 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/21 12:50:51 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	mark_redirection_as_previous(t_token_node **token, t_token_node **previous_token)
{
	if (*token && (*token)->token.type == REDIRECTION)
	{
		if (!*previous_token)
			(*token)->left = NULL;
		*previous_token = *token;
		*token = (*token)->next;
		return (true);
	}
	return (false);
}

bool	join_redirection_to_cmd(t_token_node **token, t_token_node **previous_token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD || (*token)->token.type == SIMPLE_CMD))
	{
		if (*previous_token && (*previous_token)->token.type == REDIRECTION)
		{
			(*token)->left = *previous_token;
			*previous_token = NULL;
		}
		else
			(*token)->left = NULL;
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			if (!(*token)->left)
			{
				(*token)->left = (*token)->next;
				(*token)->right = NULL;
			}
			else
				(*token)->right = (*token)->next;
			if ((*token)->next->next)
			{
				*previous_token = *token;
				*token = (*token)->next->next;
			}
			else
			{
				(*token)->next = NULL;
				return (false);
			}
		}
		else
		{
			*previous_token = *token;
			*token = (*token)->next;
		}
		return (true);
	}
	return (false);
}

bool	mark_cmd_as_previous(t_token_node **token, t_token_node **previous_token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD || (*token)->token.type == SIMPLE_CMD))
	{
		*previous_token = *token;
		*token = (*token)->next;
		return (true);
	}
	return (false);
}

bool	join_cmd_to_pipe(t_token_node **token, t_token_node **previous_token)
{
	if (*token && (*token)->token.type == PIPE)
	{
		if (*previous_token)
			(*token)->left = *previous_token;
		if ((*token)->next && (*token))
			(*token)->right = (*token)->next;
		if ((*token)->next->next)
		{
			*previous_token = *token;
			*token = (*token)->next->next;
		}
		else
			(*token)->next = NULL;
		return (true);
	}
	return (false);
}
