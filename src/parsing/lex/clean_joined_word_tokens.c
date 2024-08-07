/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_joined_word_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:45 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:59:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_vars_for_clean_joined_word_tokens
 * ------------------------------------------------
 * Initializes variables for the clean_joined_word_tokens function.
 * 
 * tokens: Pointer to the head of the tokens linked list.
 * vars: Pointer to the structure holding variables for cleaning joined word tokens.
 * 
 * This function initializes the variables used in the clean_joined_word_tokens function,
 * setting up the head of the tokens list, a temporary token pointer, and a flag indicating
 * the first command token.
 */
static void	init_vars_for_clean_joined_word_tokens(t_token_node **tokens,
    t_vars_clean_joined_word_tokens *vars)
{
    vars->head = *tokens;
    vars->tmp = NULL;
    vars->first_cmd = false;
}

/* Function: clean_joined_word_tokens
 * -----------------------------------
 * Cleans joined word tokens from the tokens linked list.
 * 
 * tokens: Pointer to the head of the tokens linked list.
 * 
 * This function iterates through the tokens linked list and removes any unnecessary
 * word tokens that are joined together, ensuring that only the first command or built-in
 * command token in a sequence before a pipe or the end of the list is kept.
 */
void	clean_joined_word_tokens(t_token_node **tokens)
{
    t_vars_clean_joined_word_tokens	vars;

    init_vars_for_clean_joined_word_tokens(tokens, &vars);
    if ((*tokens)->token.type == BUILTIN_CMD
        || (*tokens)->token.type == SIMPLE_CMD)
        vars.first_cmd = true;
    while (*tokens)
    {
        if ((*tokens)->token.type == PIPE)
            vars.first_cmd = false;
        if ((*tokens)->next && ((*tokens)->next->token.type == BUILTIN_CMD
                || (*tokens)->next->token.type == SIMPLE_CMD))
        {
            if (!vars.first_cmd)
                vars.first_cmd = true;
            else
            {
                clean_word_token(tokens, &vars.tmp);
                continue ;
            }
        }
        *tokens = (*tokens)->next;
    }
    *tokens = vars.head;
}

/* Function: clean_word_token
 * ---------------------------
 * Cleans a single word token from the tokens linked list.
 * 
 * tokens: Pointer to the current token in the tokens linked list.
 * tmp: Pointer to a temporary token node, used for re-linking the list after removal.
 * 
 * This function removes a word token from the tokens linked list, freeing its memory
 * and ensuring the integrity of the list is maintained by correctly linking the surrounding
 * tokens.
 */
void	clean_word_token(t_token_node **tokens, t_token_node **tmp)
{
    if ((*tokens)->next->next)
    {
        *tmp = (*tokens)->next->next;
        free_double_arr((*tokens)->next->token.word_val);
        free((*tokens)->next);
        (*tokens)->next = *tmp;
    }
    else
    {
        free_double_arr((*tokens)->next->token.word_val);
        free((*tokens)->next);
        (*tokens)->next = NULL;
    }
}