/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:49:40 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:33:18 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: free_prompt
 * ---------------------
 * Frees the memory allocated for the start pointer in the prompt structure.
 * 
 * prompt: A pointer to the prompt structure whose start pointer is to be freed.
 */
void	free_prompt(t_prompt *prompt)
{
    free(prompt->start_ptr_save);
}

/* Function: free_double_arr
 * --------------------------
 * Frees a dynamically allocated array of strings.
 * 
 * arr: A pointer to the array of strings to be freed.
 * 
 * This function iterates through the array, freeing each string, before freeing
 * the array itself.
 */
void	free_double_arr(char **arr)
{
    int	i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

/* Function: free_single_quote_checker_list
 * ----------------------------------------
 * Frees a linked list used for checking single quotes in the prompt.
 * 
 * prompt: A pointer to the prompt structure containing the linked list.
 * 
 * This function iterates through the linked list, freeing each node until
 * the entire list is freed and the head pointer is set to NULL.
 */
void	free_single_quote_checker_list(t_prompt *prompt)
{
    t_single_quote_checker	*current;
    t_single_quote_checker	*next;

    current = prompt->checker;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    prompt->checker = NULL;
}

/* Function: free_tree
 * -------------------
 * Recursively frees a binary tree of token nodes.
 * 
 * node: A pointer to the root node of the tree to be freed.
 * 
 * This function recursively traverses the binary tree in post-order, freeing
 * each node after its child nodes have been freed.
 */
void	free_tree(t_token_node *node)
{
    if (node->left)
        free_tree(node->left);
    if (node->right)
        free_tree(node->right);
    free(node);
}

/* Function: free_cmd_table
 * ------------------------
 * Frees a linked list of command tables.
 * 
 * table: A pointer to the head of the list of command tables to be freed.
 * 
 * This function iterates through the list of command tables, freeing associated
 * input and output file names, truncation flags, and the array of command arguments,
 * before freeing each command table node until the entire list is freed and the head
 * pointer is set to NULL.
 */
void	free_cmd_table(t_cmd **table)
{
    t_cmd	*current;
    t_cmd	*next;

    current = *table;
    while (current)
    {
        next = current->next;
        if (current->in.file_name)
            free_double_arr(current->in.file_name);
        if (current->out.file_name)
            free_double_arr(current->out.file_name);
        if (current->out.file_name && current->out.trunc)
            free(current->out.trunc);
        if (current->arr)
            free_double_arr(current->arr);
        free(current);
        current = next;
    }
    *table = NULL;
}