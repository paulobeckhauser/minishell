/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:46:42 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 12:47:04 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_node	*init_binary_tree(t_token_node *token)
{
	t_token_node	*last_token;
	t_token_node	*previous_token;

	if (token->token.type == PIPE)
	{
		perror("bash: syntax error near unexpected token `|'");
		return (NULL);
	}
	last_token = NULL;
	previous_token = NULL;
	while (token->next)
	{
		if ((!previous_token || (previous_token && previous_token->token.type != PIPE))
			&& (token->token.type == BUILTIN_CMD || token->token.type == SIMPLE_CMD))
		{
			if (!previous_token)
				token->left = NULL;
			else
				token->left = previous_token;
			token->right = NULL;
			if (!last_token)
				last_token = token;
			previous_token = token;
			token = token->next;
			previous_token->next = NULL;
		}
		else if (token->token.type == PIPE)
		{
			token->left = previous_token;
			if (token->next && (token->next->token.type == BUILTIN_CMD
				|| token->next->token.type == SIMPLE_CMD))
				token->right = token->next;
			else
				return (NULL);
			if (token->next && token->next->next)
			{
				previous_token = token;
				token = token->next;
				previous_token->next = NULL;
			}
			else
				token->next = NULL;
		}
		else
			token = token->next;
	}
	if ((!previous_token || (previous_token && previous_token->token.type != PIPE))
		&& (token->token.type == BUILTIN_CMD || token->token.type == SIMPLE_CMD))
	{
		if (!previous_token)
			token->left = NULL;
		else
			token->left = previous_token;
		token->right = NULL;
	}
	else if (token->token.type == PIPE && !token->right)
	{
		token->left = previous_token;
		if (token->next && (token->next->token.type == BUILTIN_CMD
			|| token->next->token.type == SIMPLE_CMD))
			token->right = token->next;
		else
			token->right = NULL;
	}
	return (token);
}

void	init_cmd_table(t_token_node *node, t_cmd **table, t_cmd **head, t_input *input)
{
	t_cmd	*new_cmd;

	if (!node)
		return ;
	new_cmd = NULL;
	if (node && !node->left && !node->right)
		*head = init_cmd(node, input);
	if (node && node->left && node->left->right)
		init_cmd_table(node->left, table, head, input);
	if (node->token.type != PIPE)
		return ;
	if (node->left->token.type != PIPE)
	{
		new_cmd = init_cmd(node->left, input);
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
	new_cmd = init_cmd(node->right, input);
	(*table)->next = new_cmd;
	*table = (*table)->next;
	node->right = NULL;
}

t_cmd	*init_cmd(t_token_node *node, t_input *input)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = node->token.type;
	cmd->arr = node->token.t_value.double_ptr;
	if (node->index != input->token_count - 1 && node->index != 0)
	{
		cmd->in_pipe = true;
		cmd->out_pipe = true;
	}
	else if (node->index == 0 && input->token_count > 0)
	{
		cmd->in = STDIN_FILENO;
		cmd->out_pipe = true;
	}
	else if (node->index == input->token_count - 1 && input->token_count > 0)
	{
		cmd->in_pipe = true;
		cmd->out = STDOUT_FILENO;
	}
	else
	{
		cmd->in = STDIN_FILENO;
		cmd->out = STDOUT_FILENO;
	}
	if (node->index == input->token_count - 1)
		cmd->next = NULL;
	return (cmd);
}
