/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_tree_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:47:52 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/20 19:44:59 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	init_redirection_tree_branch(t_token_node **token, t_token_node **previous_token)
{
	if ((!*previous_token && (*token)->token.type == REDIRECTION)
		|| (*previous_token && (*previous_token)->token.type != PIPE
		&& (*previous_token)->token.type != BUILTIN_CMD
		&& (*previous_token)->token.type != SIMPLE_CMD
		&& (*token)->token.type == REDIRECTION))
	{
		if (!*previous_token)
			(*token)->left = NULL;
		*previous_token = *token;
		*token = (*token)->next;
		(*previous_token)->next = NULL;
		return (true);
	}
	return (false);
}

bool	mark_redirection_as_previous(t_token_node **token, t_token_node **previous_token)
{
	if (*token && (*token)->token.type == REDIRECTION)
	{
		if (!*previous_token)
			(*token)->left = NULL;
		*previous_token = *token;
		*token = (*token)->next;
		(*previous_token)->next = NULL;
		return (true);
	}
	return (false);
}

bool	join_redirection_to_cmd(t_token_node **token, t_token_node **previous_token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD || (*token)->token.type == SIMPLE_CMD))
	{
		if (*previous_token)
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
				*token = (*token)->next;
				*previous_token = *token;
				*token = (*token)->next;
				*previous_token = NULL;
			}
			else
			{
				(*token)->next = NULL;
				return (false);
			}
		}
		else
			*token = (*token)->next;
		return (true);
	}
	return (false);
}

bool	mark_cmd_as_previous(t_token_node **token, t_token_node **previous_token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD || (*token)->token.type == SIMPLE_CMD))
	{
		if (!*previous_token)
			(*token)->left = NULL;
		*previous_token = *token;
		*token = (*token)->next;
		(*previous_token)->next = NULL;
		return (true);
	}
	return (false);
}

bool	init_cmd_tree_branch(t_token_node **token, t_token_node **previous_token)
{
	if ((*token)->token.type == BUILTIN_CMD || (*token)->token.type == SIMPLE_CMD)
	{
		if (!*previous_token)
			(*token)->left = NULL;
		else if (*previous_token && (*previous_token)->token.type == REDIRECTION)
			(*token)->left = *previous_token;
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			if (!(*token)->left)
			{
				(*token)->left = (*token)->next;
				(*token)->right = NULL;
			}
			else
				(*token)->right = (*token)->next;
			if (!(*token)->next->next && *previous_token && (*previous_token)->token.type == REDIRECTION)
				*token = *previous_token;
		}
		else
			(*token)->right = NULL;
		if (!*previous_token || (*previous_token && (*previous_token)->token.type != PIPE))
			*previous_token = *token;
		if (*token && (*token)->next && (*token)->next->next)
			*token = (*token)->next;
		else
			(*token)->next = NULL;
		return (true);
	}
	return (false);
}

// bool	init_cmd_tree_branch(t_token_node **token, t_token_node **previous_token)
// {
// 	if ((!*previous_token || (*previous_token && (*previous_token)->token.type != PIPE))
// 		&& ((*token)->token.type == BUILTIN_CMD || (*token)->token.type == SIMPLE_CMD))
// 	{
// 		if (!*previous_token && (*token)->next && (*token)->next->token.type != REDIRECTION)
// 			(*token)->left = NULL;
// 		else if (*previous_token && (*previous_token)->token.type == REDIRECTION)
// 			(*token)->left = (*previous_token);
// 		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
// 		{
// 			if (!(*token)->left)
// 				(*token)->left = (*token)->next;
// 			else
// 				(*token)->right = (*token)->next;
// 		}
// 		*previous_token = *token;
// 		*token = (*token)->next;
// 		(*previous_token)->next = NULL;
// 		return (true);
// 	}
// 	return (false);
// }

bool	join_cmd_to_pipe(t_token_node **token, t_token_node **previous_token)
{
	if (*token && (*token)->token.type == PIPE)
	{
		if (*previous_token)
			(*token)->left = *previous_token;
		if ((*token)->next)
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

bool	init_pipe_tree_branch(t_token_node **token, t_token_node **previous_token, t_prompt *prompt)
{
	if ((*token)->token.type == PIPE)
	{
		prompt->pipe_count--;
		(*token)->left = *previous_token;
		if ((*token)->next && ((*token)->next->token.type == BUILTIN_CMD
			|| (*token)->next->token.type == SIMPLE_CMD))
		{
			(*token)->right = (*token)->next;
			if (prompt->pipe_count == 0 && (*token)->next && (*token)->next->next &&
				(*token)->next->next->token.type == REDIRECTION)
				init_cmd_tree_branch(&(*token)->next, NULL);
		}
		else if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			if ((*token)->next->next->token.type == SIMPLE_CMD
				|| (*token)->next->next->token.type == BUILTIN_CMD)
				{
					init_cmd_tree_branch(&(*token)->next->next, &(*token)->next);
					(*token)->right = (*token)->next;
				}
		}
		if (prompt->pipe_count > 0)
		{
			*previous_token = *token;
			*token = (*token)->next;
			(*previous_token)->next = NULL;
		}
		else
			(*token)->next = NULL;
		return (true);
	}
	return (false);
}
