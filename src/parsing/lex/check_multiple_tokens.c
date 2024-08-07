/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multiple_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:13:25 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:58:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: if_multiple_redirections
 * -----------------------------------
 * Checks if there are multiple redirections in a sequence of tokens.
 * 
 * tokens: A linked list of token nodes to be checked.
 * 
 * Returns 1 if multiple redirections are found in a sequence without a PIPE token
 * separating them, otherwise returns 0.
 */
int	if_multiple_redirections(t_token_node *tokens)
{
    bool	first;

    first = false;
    while (tokens)
    {
        if (tokens->token.type == PIPE)
            first = false;
        if (tokens->token.type == REDIRECTION)
        {
            if (!first)
                first = true;
            else
                return (1);
        }
        tokens = tokens->next;
    }
    return (0);
}

/* Function: if_multiple_word_tokens
 * ----------------------------------
 * Checks if there are multiple command or built-in command tokens in a sequence of tokens.
 * 
 * tokens: A linked list of token nodes to be checked.
 * 
 * Returns 1 if multiple SIMPLE_CMD or BUILTIN_CMD tokens are found in a sequence without
 * a PIPE token separating them, otherwise returns 0.
 */
int	if_multiple_word_tokens(t_token_node *tokens)
{
    bool	first;

    first = false;
    while (tokens)
    {
        if (tokens->token.type == PIPE)
            first = false;
        if (tokens->token.type == SIMPLE_CMD
            || tokens->token.type == BUILTIN_CMD)
        {
            if (!first)
                first = true;
            else
                return (1);
        }
        tokens = tokens->next;
    }
    return (0);
}