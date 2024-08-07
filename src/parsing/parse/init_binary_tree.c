/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:01:22 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:24:42 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_binary_tree
 * ---------------------------
 * Initializes the binary tree for command execution.
 * 
 * token: A double pointer to the head of the token list.
 * 
 * Returns: A pointer to the root of the binary tree.
 * 
 * This function initializes the binary tree for command execution by first
 * finding the first command token in the list. It then plants redirections
 * around this command and deletes redirection tokens from the list. Finally,
 * it plants the command in the binary tree and returns the root of the tree.
 */
t_token_node	*init_binary_tree(t_token_node **token)
{
	t_token_node	*root;
	t_token_node	*head;

	if (!(*token)->next)
		return (*token);
	root = NULL;
	head = NULL;
	find_first_cmd_token(*token, &head);
	plant_redirections(token, &root);
	*token = head;
	delete_redirection_tokens_from_list(token, &head);
	*token = head;
	plant_cmd(token, &root);
	return (root);
}

/* Function: find_first_cmd_token
 * -------------------------------
 * Finds the first command token in the token list.
 * 
 * token: A pointer to the head of the token list.
 * head: A double pointer to store the head of the command tokens.
 * 
 * This function iterates through the token list until it finds the first
 * command token (either BUILTIN_CMD or SIMPLE_CMD) and sets it as the head.
 */
void	find_first_cmd_token(t_token_node *token, t_token_node **head)
{
	while (token)
	{
		if (token->token.type == BUILTIN_CMD || token->token.type == SIMPLE_CMD)
		{
			*head = token;
			return ;
		}
		token = token->next;
	}
}

/* Function: plant_redirections
 * -----------------------------
 * Plants redirections around the command in the binary tree.
 * 
 * token: A double pointer to the current token.
 * root: A double pointer to the root of the binary tree.
 * 
 * This function iterates through the token list and for each command token
 * found, it sets it as the root and calls join_redirection_to_cmd to attach
 * redirections to it.
 */
void	plant_redirections(t_token_node **token, t_token_node **root)
{
	while (*token)
	{
		if ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD)
		{
			*root = *token;
			join_redirection_to_cmd(token);
		}
		*token = (*token)->next;
	}
}

/* Function: delete_redirection_tokens_from_list
 * ----------------------------------------------
 * Deletes redirection tokens from the token list.
 * 
 * token: A double pointer to the current token.
 * head: A double pointer to the head of the command tokens.
 * 
 * This function iterates through the token list and removes redirection tokens,
 * adjusting the next and prev pointers accordingly. It ensures the list integrity
 * by fixing the prev pointers after deletions.
 */
void	delete_redirection_tokens_from_list(t_token_node **token,
	t_token_node **head)
{
	while (*token && (*token)->token.type == REDIRECTION)
		*token = (*token)->next;
	*head = *token;
	while (*token)
	{
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			(*token)->next = (*token)->next->next;
			if ((*token)->next)
				(*token)->next->prev = *token;
		}
		else
			*token = (*token)->next;
	}
	*token = *head;
	fix_prev_pointers(token);
	*token = *head;
}

/* Function: plant_cmd
 * --------------------
 * Plants the command in the binary tree.
 * 
 * token: A double pointer to the current token.
 * root: A double pointer to the root of the binary tree.
 * 
 * This function iterates through the token list and for each PIPE token found,
 * it sets it as the root and calls join_tokens_to_pipe to attach commands to it.
 * This effectively builds the structure of the binary tree for command execution.
 */
void	plant_cmd(t_token_node **token, t_token_node **root)
{
	t_token_node	*first_pipe;

	first_pipe = NULL;
	while (*token)
	{
		if ((*token)->token.type == PIPE)
		{
			*root = *token;
			join_tokens_to_pipe(token, &first_pipe);
		}
		*token = (*token)->next;
	}
}