/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:01:22 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/19 12:41:36 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_token_node	*init_binary_tree(t_token_node **token)
{
	t_token_node	*root;
	t_token_node	*head;

	if (!(*token)->next)
		return (*token);
	root = NULL;
	head = NULL;
	find_first_cmd_token(*token, &head);
	plant_redirections(token, &root);
	*token = head;
	delete_redirection_tokens_from_list(token, &head);
	*token = head;
	plant_cmd(token, &root);
	return (root);
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

void	plant_redirections(t_token_node **token, t_token_node **root)
{
	while (*token)
	{
		if ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD)
		{
			*root = *token;
			join_redirection_to_cmd(token);
		}
		*token = (*token)->next;
	}
}

void	delete_redirection_tokens_from_list(t_token_node **token,
	t_token_node **head)
{
	t_token_node	*curr;

	while (*token && (*token)->token.type == REDIRECTION)
		*token = (*token)->next;
	*head = *token;
	while (*token)
	{
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			(*token)->next = (*token)->next->next;
			if ((*token)->next)
				(*token)->next->prev = *token;
		}
		else
			*token = (*token)->next;
	}
	*token = *head;
	(*token)->prev = NULL;
	while (*token)
	{
		curr = *token;
		*token = (*token)->next;
		if (*token)
			(*token)->prev = curr;
	}
	*token = *head;
}

void	plant_cmd(t_token_node **token, t_token_node **root)
{
	t_token_node	*first_pipe;

	first_pipe = NULL;
	while (*token)
	{
		if ((*token)->token.type == PIPE)
		{
			*root = *token;
			join_tokens_to_pipe(token, &first_pipe);
		}
		*token = (*token)->next;
	}
}
