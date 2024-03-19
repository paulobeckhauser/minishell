/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_cmd_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:46:42 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/19 18:43:48 by sfrankie         ###   ########.fr       */
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
		if (init_redirection_tree_branch(token, &previous_token))
			continue ;
		if (init_cmd_tree_branch(token, &previous_token))
			continue ;
		else if (init_pipe_tree_branch(token, &previous_token))
			continue ;
		else
			*token = (*token)->next;
	}
	return (*token);
}

void	init_cmd_table(t_token_node *node, t_cmd **table, t_cmd **head, t_prompt *prompt)
{
	t_cmd	*new_cmd;

	if (!node)
		return ;
	new_cmd = NULL;
	if (node && !node->left && !node->right)
		*head = init_cmd(node, prompt);
	if (node && node->left && node->left->right)
		init_cmd_table(node->left, table, head, prompt);
	if (node->token.type != PIPE)
		return ;
	if (node->left->token.type != PIPE)
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
	new_cmd = init_cmd(node->right, prompt);
	(*table)->next = new_cmd;
	*table = (*table)->next;
	node->right = NULL;
}

t_cmd	*init_cmd(t_token_node *node, t_prompt *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = node->token.type;
	cmd->arr = node->token.t_value.double_ptr;
	if (node->index == prompt->token_count - 1)
		cmd->next = NULL;
	return (cmd);
}
