/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_cmd_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:46:42 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/29 19:20:23 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_node	*init_binary_tree(t_token_node **token)
{
	t_token_node	*previous_token;
	t_token_node	*head;

	if ((*token)->token.type == PIPE)
	{
		perror("bash: syntax error near unexpected token `|'");
		return (NULL);
	}
	if (!(*token)->next)
		return (*token);
	previous_token = NULL;
	head = NULL;
	find_first_cmd_token(*token, &head);
	while (*token)
	{
		if (mark_redirection_as_previous(token, &previous_token))
			continue ;
		else if (join_redirection_to_cmd(token, &previous_token))
			continue ;
		else
			*token = (*token)->next;
	}
	*token = head;
	delete_redirection_tokens_from_list(token, &head);
	*token = head;
	while ((*token)->next)
	{
		if (mark_cmd_as_previous(token, &previous_token))
			continue ;
		else if (join_cmd_to_pipe(token, &previous_token))
			continue ;
		else
			*token = (*token)->next;
	}
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

void	delete_redirection_tokens_from_list(t_token_node **token, t_token_node **head)
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

void	init_cmd_table(t_token_node *node, t_cmd **table, t_cmd **head, t_prompt *prompt)
{
	t_cmd	*new_cmd;

	if (!node)
		return ;
	new_cmd = NULL;
	if (prompt->pipe_count == 0)
	{
		new_cmd = init_cmd(node, prompt);
		*head = new_cmd;
		return ;
	}
	if (node && node->left && node->left->right && node->left->right->token.type != REDIRECTION)
		init_cmd_table(node->left, table, head, prompt);
	if (!node || (node && node->token.type != PIPE))
		return ;
	if (node->left && node->left->token.type != PIPE)
	{
		new_cmd = init_cmd(node->left, prompt);
		if (!*head)
			*head = new_cmd;
		if (!*table)
			*table = new_cmd;
		else
		{
			(*table)->next = new_cmd;
			*table = (*table)->next;
		}
		node->left = NULL;
	}
	if (node->right && node->right->token.type != PIPE)
	{
		new_cmd = init_cmd(node->right, prompt);
		(*table)->next = new_cmd;
		*table = (*table)->next;
		node->right = NULL;
	}
}

t_cmd	*init_cmd(t_token_node *node, t_prompt *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = node->token.type;
	cmd->arr = node->token.t_value.double_ptr;
	if (node->left)
	{
		if ((node->left->token.t_value.single_ptr[0] == '<'
			&& ft_strlen(node->left->token.t_value.single_ptr) == 1)
			|| (node->left->token.t_value.single_ptr[0] == '<'
			&& node->left->token.t_value.single_ptr[1] == '<'))
			cmd->in = node->left->token.in;
		else
			cmd->out = node->left->token.out;
	}
	if (node->right)
	{
		if ((node->right->token.t_value.single_ptr[0] == '<'
			&& ft_strlen(node->right->token.t_value.single_ptr) == 1)
			|| (node->right->token.t_value.single_ptr[0] == '<'
			&& node->right->token.t_value.single_ptr[1] == '<'))
			cmd->in = node->right->token.in;
		else
			cmd->out = node->right->token.out;
	}
	if (node->index == prompt->token_count - 1)
		cmd->next = NULL;
	return (cmd);
}
