/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_no_cmd_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:05:27 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:23:57 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: if_no_cmd_tokens
 * --------------------------
 * Checks if the token list contains no command tokens.
 * 
 * tokens: A pointer to the head of the token list.
 * 
 * Returns: true if there are no BUILTIN_CMD or SIMPLE_CMD tokens in the list,
 * false otherwise.
 * 
 * This function iterates through the token list. If it finds a token with the
 * type BUILTIN_CMD or SIMPLE_CMD, it returns false, indicating that there are
 * command tokens in the list. If it reaches the end of the list without finding
 * any command tokens, it returns true, indicating that there are no command
 * tokens in the list.
 */
bool	if_no_cmd_tokens(t_token_node *tokens)
{
	while (tokens)
	{
		if (tokens->token.type == BUILTIN_CMD
			|| tokens->token.type == SIMPLE_CMD)
			return (false);
		tokens = tokens->next;
	}
	return (true);
}