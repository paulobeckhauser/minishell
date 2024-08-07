/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:57:44 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 13:31:56 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: free_token_list
 * --------------------------
 * Frees a list of token nodes.
 * 
 * list: A pointer to the head of the list to be freed.
 * 
 * This function iterates through the list of token nodes, freeing each node
 * until the entire list is freed and the head pointer is set to NULL.
 */
void	free_token_list(t_token_node **list)
{
    t_token_node	*current;
    t_token_node	*next;

    current = *list;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *list = NULL;
}

/* Function: free_redirect_files
 * -----------------------------
 * Frees the file names associated with redirection tokens.
 * 
 * current: The current token node being processed.
 * 
 * If the current token is of type REDIRECTION, this function frees the memory
 * allocated for input and output file names, including the truncation flag for output.
 */
static void	free_redirect_files(t_token_node *current)
{
    if (current->token.type == REDIRECTION)
    {
        if (current->token.in.file_name)
            free_double_arr(current->token.in.file_name);
        if (current->token.out.file_name)
        {
            if (current->token.out.trunc)
                free(current->token.out.trunc);
            free_double_arr(current->token.out.file_name);
        }
    }
}

/* Function: free_builtin_or_simpl_cmd
 * -----------------------------------
 * Frees the word values for builtin or simple command tokens.
 * 
 * current: The current token node being processed.
 * 
 * If the current token is of type BUILTIN_CMD or SIMPLE_CMD and has word values,
 * this function frees the memory allocated for those word values.
 */
static void	free_builtin_or_simpl_cmd(t_token_node *current)
{
    if ((current->token.type == BUILTIN_CMD
            || current->token.type == SIMPLE_CMD) && current->token.word_val)
        free_double_arr(current->token.word_val);
}

/* Function: free_token_list_full
 * -------------------------------
 * Frees a list of token nodes and associated data.
 * 
 * list: A pointer to the head of the list to be freed.
 * 
 * This function iterates through the list of token nodes, freeing associated data
 * such as file names for redirections and word values for commands, before freeing
 * each node until the entire list is freed and the head pointer is set to NULL.
 */
void	free_token_list_full(t_token_node **list)
{
    t_token_node	*current;
    t_token_node	*next;

    current = *list;
    while (current != NULL)
    {
        next = current->next;
        free_redirect_files(current);
        free_builtin_or_simpl_cmd(current);
        free(current);
        current = next;
    }
    *list = NULL;
}