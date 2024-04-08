/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:47:21 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/07 21:48:55 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_token_node	*init_binary_tree(t_token_node **token)
{
	t_token_node	*previous_token;
	t_token_node	*head;

	if (!(*token)->next)
		return (*token);
	previous_token = NULL;
	head = NULL;
	find_first_cmd_token(*token, &head);
	plant_redirections(token, &previous_token);
	*token = head;
	delete_redirection_tokens_from_list(token, &head);
	*token = head;
	plant_cmd(token, &head);
	return (*token);
}

void	find_first_cmd_token(t_token_node *token, t_token_node **head)
{
	while (token)
	{
		if (token->token.type == BUILTIN_CMD || token->token.type == SIMPLE_CMD)
		{
			*head = token;
			return ;
		}
		token = token->next;
	}
}

void	plant_redirections(t_token_node **token, t_token_node **previous_token)
{
	while (*token)
	{
		if (mark_redirection_as_previous(token, previous_token))
			continue ;
		else if (join_redirection_to_cmd(token, previous_token))
			continue ;
		else
			*token = (*token)->next;
	}
}

void	delete_redirection_tokens_from_list(t_token_node **token,
	t_token_node **head)
{
	while (*token && (*token)->token.type == REDIRECTION)
		*token = (*token)->next;
	*head = *token;
	while (*token)
	{
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
			(*token)->next = (*token)->next->next;
		else
			*token = (*token)->next;
	}
}

void	plant_cmd(t_token_node **token, t_token_node **previous_token)
{
	while ((*token)->next)
	{
		if (mark_cmd_as_previous(token, previous_token))
			continue ;
		else if (join_cmd_to_pipe(token, previous_token))
			continue ;
		else
			*token = (*token)->next;
	}
}
