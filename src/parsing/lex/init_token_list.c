/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:43:51 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 14:01:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_token_list
 * --------------------------
 * Initializes a linked list of tokens based on the input from the prompt.
 * 
 * structure: Pointer to the main structure containing shell information.
 * prompt: Pointer to the prompt structure containing the user input.
 * 
 * Returns a pointer to the head of the linked list of tokens.
 * Initializes tokens by parsing the input from the prompt and creating a linked list
 * of tokens. Handles errors and end of input appropriately.
 */
t_token_node	*init_token_list(t_info *structure, t_prompt *prompt)
{
    t_token_node	*list;
    t_token_node	*head;
    t_token_node	*current;
    int				i;

    head = NULL;
    current = NULL;
    list = NULL;
    i = 0;
    while (1)
    {
        list = init_token_node(structure, prompt, i++);
        if (!list)
            return (free_token_list_full(&head), NULL);
        if (list->token.type == END)
            break ;
        if (list->token.type == ERROR)
            return (free_token_list_full(&head), free(list), NULL);
        add_node_to_list(&head, &current, list);
    }
    if (if_wrong_pipe_placement(&head, &current, structure))
        return (NULL);
    prompt->token_count = i;
    return (free(list), head);
}

/* Function: init_token_node
 * --------------------------
 * Initializes a single token node.
 * 
 * structure: Pointer to the main structure containing shell information.
 * prompt: Pointer to the prompt structure containing the user input.
 * index: The index of the token in the input.
 * 
 * Returns a pointer to the initialized token node.
 * Allocates memory for a new token node, initializes it with the token information,
 * and sets its index.
 */
t_token_node	*init_token_node(t_info *structure, t_prompt *prompt, int index)
{
    t_token_node	*node;

    node = ft_calloc(1, sizeof(t_token_node));
    if (!node)
        return (NULL);
    node->token = init_token_struct(structure, prompt);
    node->next = NULL;
    node->index = index;
    return (node);
}

/* Function: add_node_to_list
 * ---------------------------
 * Adds a new token node to the linked list of tokens.
 * 
 * head: Pointer to the pointer to the head of the linked list.
 * current: Pointer to the pointer to the current node in the linked list.
 * new_node: Pointer to the new token node to be added.
 * 
 * Adds the new_node to the end of the linked list, updating the head and current pointers
 * as necessary.
 */
void	add_node_to_list(t_token_node **head, t_token_node **current,
    t_token_node *new_node)
{
    if (!*head)
    {
        *head = new_node;
        *current = new_node;
        new_node->prev = NULL;
    }
    else
    {
        new_node->prev = *current;
        (*current)->next = new_node;
        *current = (*current)->next;
    }
}

/* Function: init_token_struct
 * ----------------------------
 * Initializes a token structure based on the current position in the prompt.
 * 
 * structure: Pointer to the main structure containing shell information.
 * prompt: Pointer to the prompt structure containing the user input.
 * 
 * Returns the initialized token structure.
 * Determines the type of the next token in the input and initializes the token
 * structure accordingly.
 */
t_token	init_token_struct(t_info *structure, t_prompt *prompt)
{
    t_type	type;
    t_token	token;

    type = find_token(prompt);
    if (type == PIPE)
        token = init_pipe_token(prompt);
    else if (type == REDIRECTION)
        token = init_redirection_token(prompt);
    else if (type == WORD)
        token = init_cmd_token(structure, prompt);
    else
        token = init_end_token();
    if (type != WORD && type != REDIRECTION)
        prompt->msg++;
    return (token);
}

/* Function: find_token
 * --------------------
 * Identifies the type of the next token in the prompt.
 * 
 * prompt: Pointer to the prompt structure containing the user input.
 * 
 * Returns the type of the next token.
 * Skips whitespace and identifies the type of the next token based on the
 * current character in the prompt.
 */
t_type	find_token(t_prompt *prompt)
{
    t_type	type;

    if (prompt->start_ptr_save == NULL)
        prompt->start_ptr_save = prompt->msg;
    prompt->word_count = 0;
    skip_whitespaces(prompt);
    if (*prompt->msg == 0)
        type = END;
    if (ft_strchr(prompt->symbols, *prompt->msg))
    {
        if (*prompt->msg == '|' && *(prompt->msg + 1) != '|')
            type = PIPE;
        else if (*prompt->msg == '<' || *prompt->msg == '>')
            type = REDIRECTION;
    }
    else
        type = WORD;
    return (type);
}