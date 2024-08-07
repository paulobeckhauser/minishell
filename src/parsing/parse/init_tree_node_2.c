/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree_node_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:45:15 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:25:50 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: join_right_token_to_pipe
 * -----------------------------------
 * Attaches the right command token to a pipe token in the binary tree.
 * 
 * token: A double pointer to the current token, which should be a PIPE token.
 * 
 * This function checks if the next token in the list is a command token
 * (either BUILTIN_CMD or SIMPLE_CMD). If so, it sets this command token as
 * the right child of the current PIPE token.
 */
void	join_right_token_to_pipe(t_token_node **token)
{
	if ((*token)->next && ((*token)->next->token.type == BUILTIN_CMD
			|| (*token)->next->token.type == SIMPLE_CMD))
		(*token)->right = (*token)->next;
}