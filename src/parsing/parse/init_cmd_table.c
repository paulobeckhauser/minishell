/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:46:42 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:25:31 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_cmd_table
 * -------------------------
 * Initializes the command table for execution.
 * 
 * node: The current node in the binary tree of tokens.
 * table: A pointer to the command table being built.
 * head: A pointer to the head of the command table.
 * prompt: The current prompt information, including pipe count.
 * 
 * This function recursively traverses the binary tree of tokens to initialize
 * the command table. It handles different cases based on the presence of pipes
 * and redirections, and constructs the command table accordingly.
 */
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

/* Function: init_left_leaf
 * -------------------------
 * Initializes the left leaf of the current node as a command in the command table.
 * 
 * node: A pointer to the current node in the binary tree.
 * table: A pointer to the command table being built.
 * head: A pointer to the head of the command table.
 * prompt: The current prompt information.
 * 
 * This function initializes the left leaf of the current node as a command and
 * updates the command table and its head accordingly.
 */
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

/* Function: init_right_leaf
 * --------------------------
 * Initializes the right leaf of the current node as a command in the command table.
 * 
 * node: A pointer to the current node in the binary tree.
 * table: A pointer to the command table being built.
 * prompt: The current prompt information.
 * 
 * This function initializes the right leaf of the current node as a command and
 * updates the command table accordingly.
 */
void	init_right_leaf(t_token_node **node, t_cmd **table,
	t_prompt *prompt)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd((*node)->right, prompt);
	(*table)->next = new_cmd;
	*table = (*table)->next;
}

/* Function: init_cmd
 * -------------------
 * Initializes a command from a token node.
 * 
 * node: The token node to initialize the command from.
 * prompt: The current prompt information.
 * 
 * Returns: A pointer to the initialized command.
 * 
 * This function allocates memory for a new command, assigns its input and output
 * based on the redirections found in its left and right children, and sets its
 * type, arguments, and other properties based on the token node and prompt information.
 */
t_cmd	*init_cmd(t_token_node *node, t_prompt *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	assign_type_arr_in_out(cmd, prompt, node);
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