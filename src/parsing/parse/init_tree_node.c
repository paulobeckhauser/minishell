/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:47:52 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/09 13:14:12 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	mark_redirection_as_previous(t_token_node **token,
	t_token_node **previous_token)
{
	if (*token && (*token)->token.type == REDIRECTION)
	{
		if (!*previous_token)
			(*token)->left = NULL;
		else if (*previous_token
			&& (*previous_token)->token.type == REDIRECTION)
			(*token)->left = *previous_token;
		*previous_token = *token;
		*token = (*token)->next;
		return (true);
	}
	return (false);
}

bool	join_redirection_to_cmd(t_token_node **token,
	t_token_node **previous_token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD))
	{
		if (*previous_token && (*previous_token)->token.type == REDIRECTION)
		{
			(*token)->left = *previous_token;
			if ((*previous_token)->left)
				(*token)->right = (*previous_token)->left;
		}
		else
			(*token)->left = NULL;
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			if (!join_next_redirection_to_cmd(token, previous_token))
				return (false);
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

bool	join_next_redirection_to_cmd(t_token_node **token,
	t_token_node **previous_token)
{
	if (!(*token)->left)
	{
		(*token)->left = (*token)->next;
		(*token)->right = NULL;
		if ((*token)->next->next
			&& (*token)->next->next->token.type == REDIRECTION)
			(*token)->right = (*token)->next->next;
	}
	else
	{
		(*token)->right = (*token)->next;
	}
	if ((*token)->next->next
		&& (*token)->next->next->token.type != REDIRECTION)
	{
		*previous_token = *token;
		*token = (*token)->next->next;
	}
	else
	{
		(*token)->next = NULL;
		return (false);
	}
	return (true);
}

bool	mark_cmd_as_previous(t_token_node **token,
	t_token_node **previous_token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD))
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
		if (*token && (*token)->next)
			(*token)->right = (*token)->next;
		if (*token && (*token)->next && (*token)->next->next)
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
