/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_tree_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:47:52 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/17 20:01:07 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	init_cmd_tree_branch(t_token_node **token, t_token_node **previous_token)
{
	if ((!*previous_token || (*previous_token && (*previous_token)->token.type != PIPE))
		&& ((*token)->token.type == BUILTIN_CMD || (*token)->token.type == SIMPLE_CMD))
	{
		if (!*previous_token)
			(*token)->left = NULL;
		else
			(*token)->left = *previous_token;
		(*token)->right = NULL;
		*previous_token = *token;
		*token = (*token)->next;
		(*previous_token)->next = NULL;
		return (true);
	}
	return (false);
}

bool	init_pipe_tree_branch(t_token_node **token, t_token_node **previous_token)
{
	if ((*token)->token.type == PIPE)
	{
		(*token)->left = *previous_token;
		if ((*token)->next && ((*token)->next->token.type == BUILTIN_CMD
			|| (*token)->next->token.type == SIMPLE_CMD))
			(*token)->right = (*token)->next;
		else
			return (NULL);
		if ((*token)->next && (*token)->next->next)
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