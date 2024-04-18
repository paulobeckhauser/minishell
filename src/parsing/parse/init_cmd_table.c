/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:46:42 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/17 18:01:11 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_cmd_table(t_token_node *node, t_cmd **table, t_cmd **head,
	t_prompt *prompt)
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
	if (node && node->left && node->left->right
		&& node->left->right->token.type != REDIRECTION)
		init_cmd_table(node->left, table, head, prompt);
	if (!node || (node && node->token.type != PIPE))
		return ;
	if (node->left && node->left->token.type != PIPE)
		init_left_leaf(&node, table, head, prompt);
	if (node->right && node->right->token.type != PIPE)
		init_right_leaf(&node, table, prompt);
}

void	init_left_leaf(t_token_node **node, t_cmd **table, t_cmd **head,
	t_prompt *prompt)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd((*node)->left, prompt);
	if (!*head)
		*head = new_cmd;
	if (!*table)
		*table = new_cmd;
	else
	{
		(*table)->next = new_cmd;
		*table = (*table)->next;
	}
}

void	init_right_leaf(t_token_node **node, t_cmd **table,
	t_prompt *prompt)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd((*node)->right, prompt);
	(*table)->next = new_cmd;
	*table = (*table)->next;
}

t_cmd	*init_cmd(t_token_node *node, t_prompt *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = node->token.type;
	cmd->arr = node->token.word_val;
	cmd->in_prio = prompt->in_prio;
	cmd->out_prio = prompt->out_prio;
	if (node->left)
	{
		if (if_in_left_redirection(&node))
			cmd->in = node->left->token.in;
		else
			cmd->out = node->left->token.out;
	}
	if (node->right)
	{
		if (if_in_right_redirection(&node))
			cmd->in = node->right->token.in;
		else
			cmd->out = node->right->token.out;
	}
	if (node->index == prompt->token_count - 1)
		cmd->next = NULL;
	return (cmd);
}
