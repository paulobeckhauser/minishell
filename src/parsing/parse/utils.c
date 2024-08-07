/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:21:09 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:28:01 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: if_in_left_redirection
 * ---------------------------------
 * Checks if the left node of the current node is a single or double left redirection.
 * 
 * node: A pointer to the current node in the token list.
 * 
 * Returns true if the left node is a single ('<') or double ('<<') left redirection,
 * otherwise returns false.
 */
bool	if_in_left_redirection(t_token_node **node)
{
	if (((*node)->left->token.val[0] == '<'
			&& ft_strlen((*node)->left->token.val) == 1)
		|| ((*node)->left->token.val[0] == '<'
			&& (*node)->left->token.val[1] == '<'))
		return (true);
	return (false);
}

/* Function: if_in_right_redirection
 * ----------------------------------
 * Checks if the right node of the current node is a single or double left redirection.
 * 
 * node: A pointer to the current node in the token list.
 * 
 * Returns true if the right node is a single ('<') or double ('<<') left redirection,
 * otherwise returns false.
 */
bool	if_in_right_redirection(t_token_node **node)
{
	if (((*node)->right->token.val[0] == '<'
			&& ft_strlen((*node)->right->token.val) == 1)
		|| ((*node)->right->token.val[0] == '<'
			&& (*node)->right->token.val[1] == '<'))
		return (true);
	return (false);
}

/* Function: assign_type_arr_in_out
 * ---------------------------------
 * Assigns command type, array of words, input priority, and output priority from a token node.
 * 
 * cmd: A pointer to the command structure to be filled.
 * prompt: A pointer to the prompt structure containing input and output priorities.
 * node: The current token node containing the command information.
 * 
 * This function assigns the command type, array of words (arguments), input priority,
 * and output priority based on the current token node and the prompt's priorities.
 */
void	assign_type_arr_in_out(t_cmd *cmd, t_prompt *prompt, t_token_node *node)
{
	cmd->type = node->token.type;
	cmd->arr = node->token.word_val;
	cmd->in_prio = prompt->in_prio;
	cmd->out_prio = prompt->out_prio;
}