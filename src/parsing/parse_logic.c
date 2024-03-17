/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:46:42 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 17:46:45 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_node	*init_binary_tree(t_token_node **token)
{
	t_token_node	*previous_token;

	if ((*token)->token.type == PIPE)
	{
		perror("bash: syntax error near unexpected token `|'");
		return (NULL);
	}
	previous_token = NULL;
	while ((*token)->next)
	{
		if (init_cmd_tree_branch(token, &previous_token))
			continue ;
		else if (init_pipe_tree_branch(token, &previous_token))
			continue ;
		else
			*token = (*token)->next;
	}
	return (*token);
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
