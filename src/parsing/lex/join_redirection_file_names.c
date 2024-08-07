/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redirection_file_names.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:20:06 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:16:19 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: join_redirection_file_names
 * --------------------------------------
 * Joins both input and output redirection file names into a single array.
 * 
 * tokens: A pointer to the head of a linked list of token nodes.
 * 
 * This function is a wrapper that calls two other functions:
 * join_in_redirection_file_names and join_out_redirection_file_names.
 * It processes the tokens linked list to join file names for both input
 * and output redirections, ensuring that redirections are properly handled
 * in the shell's command execution.
 */
void	join_redirection_file_names(t_token_node **tokens)
{
	join_in_redirection_file_names(tokens); // Handles joining of input redirection file names
	join_out_redirection_file_names(tokens); // Handles joining of output redirection file names
}