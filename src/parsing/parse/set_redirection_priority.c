/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_priority.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:12:56 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:27:33 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: delete_repeating_redirection_tokens
 * ----------------------------------------------
 * Deletes redundant redirection tokens, keeping only the last redirection token
 * before a command or pipe.
 * 
 * tokens: A pointer to the head of the token list.
 * 
 * This function iterates through the token list, marking the last input and output
 * redirection tokens before a command or pipe. It then deletes all other redirection
 * tokens that are not marked as the last redirection.
 */
void	delete_repeating_redirection_tokens(t_token_node **tokens)
{
	t_token_node	*head;
	t_token_node	*previous_token;

	head = NULL;
	previous_token = NULL;
	while (*tokens)
	{
		if ((*tokens)->token.type == PIPE)
			*tokens = (*tokens)->next;
		mark_last_in_redirection(*tokens);
		mark_last_out_redirection(*tokens);
		delete_and_close_not_used_redirections(tokens, &head, &previous_token);
	}
	*tokens = head;
	fix_prev_pointers(tokens);
	*tokens = head;
}

/* Function: mark_last_in_redirection
 * -----------------------------------
 * Marks the last input redirection token before a command or pipe.
 * 
 * tokens: The current token in the list.
 * 
 * Iterates through the tokens until a PIPE token is encountered, marking the last
 * input redirection token (if any) as the last redirection.
 */
void	mark_last_in_redirection(t_token_node *tokens)
{
	t_token_node	*current_last;

	current_last = NULL;
	while (tokens && tokens->token.type != PIPE)
	{
		if (tokens->token.type == REDIRECTION
			&& tokens->token.val[0] == '<')
			current_last = tokens;
		tokens = tokens->next;
	}
	if (current_last)
		current_last->token.last_redirection = true;
}

/* Function: mark_last_out_redirection
 * ------------------------------------
 * Marks the last output redirection token before a command or pipe.
 * 
 * tokens: The current token in the list.
 * 
 * Iterates through the tokens until a PIPE token is encountered, marking the last
 * output redirection token (if any) as the last redirection.
 */
void	mark_last_out_redirection(t_token_node *tokens)
{
	t_token_node	*current_last;

	current_last = NULL;
	while (tokens && tokens->token.type != PIPE)
	{
		if (tokens->token.type == REDIRECTION
			&& tokens->token.val[0] == '>')
			current_last = tokens;
		tokens = tokens->next;
	}
	if (current_last)
		current_last->token.last_redirection = true;
}

/* Function: delete_and_close_not_used_redirections
 * ------------------------------------------------
 * Deletes redirection tokens that are not marked as the last redirection.
 * 
 * tokens: A pointer to the current token.
 * head: A pointer to the head of the modified token list.
 * previous_token: A pointer to the token preceding the current token.
 * 
 * This function iterates through the tokens, deleting redirection tokens that are
 * not marked as the last redirection. It maintains the linked list structure by
 * adjusting the next pointers of the remaining tokens.
 */
void	delete_and_close_not_used_redirections(t_token_node **tokens,
	t_token_node **head, t_token_node **previous_token)
{
	t_token_node	*tmp;

	tmp = NULL;
	while (*tokens)
	{
		if ((*tokens)->token.type == REDIRECTION
			&& !(*tokens)->token.last_redirection)
		{
			tmp = (*tokens);
			if (*previous_token)
				(*previous_token)->next = (*tokens)->next;
			*tokens = (*tokens)->next;
			free(tmp);
		}
		else
		{
			if (!*head)
				*head = *tokens;
			*previous_token = *tokens;
			if ((*tokens)->token.type == PIPE)
				break ;
			*tokens = (*tokens)->next;
		}
	}
}

/* Function: fix_prev_pointers
 * ----------------------------
 * Fixes the prev pointers of the token list after modifications.
 * 
 * tokens: A pointer to the head of the token list.
 * 
 * After deleting tokens, this function iterates through the list to correctly
 * set the prev pointers, ensuring the doubly linked list structure is maintained.
 */
void	fix_prev_pointers(t_token_node **tokens)
{
	t_token_node	*curr;

	curr = NULL;
	(*tokens)->prev = NULL;
	while (*tokens)
	{
		curr = *tokens;
		*tokens = (*tokens)->next;
		if (*tokens)
			(*tokens)->prev = curr;
	}
}