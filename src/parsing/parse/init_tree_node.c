/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:31:35 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:26:42 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: join_redirection_to_cmd
 * ----------------------------------
 * Attaches redirection tokens to command tokens in the binary tree.
 * 
 * token: A double pointer to the current token node.
 * 
 * This function attempts to join left redirections to the command first. If there
 * are no left redirections, it tries to join right redirections to the command.
 */
void	join_redirection_to_cmd(t_token_node **token)
{
	if (!join_left_redirections_to_cmd(token))
		join_right_redirections_to_cmd(token);
}

/* Function: join_left_redirections_to_cmd
 * ----------------------------------------
 * Attaches left redirection tokens to a command token.
 * 
 * token: A double pointer to the current token node.
 * 
 * Returns: 1 if a left redirection is successfully attached, 0 otherwise.
 * 
 * This function checks if the current token is a command and if its previous
 * token is a redirection. If so, it attaches the redirection to the command.
 * It handles the case of consecutive redirections by attaching them to the left
 * and right of the command.
 */
int	join_left_redirections_to_cmd(t_token_node **token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD))
	{
		if ((*token)->prev && (*token)->prev->token.type == REDIRECTION)
		{
			if ((*token)->prev->prev
				&& (*token)->prev->prev->token.type == REDIRECTION)
			{
				(*token)->left = (*token)->prev->prev;
				(*token)->right = (*token)->prev;
				return (1);
			}
			else
			{
				(*token)->left = (*token)->prev;
				(*token)->right = NULL;
				return (0);
			}
		}
	}
	return (0);
}

/* Function: join_right_redirections_to_cmd
 * -----------------------------------------
 * Attaches right redirection tokens to a command token.
 * 
 * token: A double pointer to the current token node.
 * 
 * This function checks if the current token is a command and if its next
 * token is a redirection. If so, it attaches the redirection to the command.
 * It handles the case of consecutive redirections by attaching them to the left
 * and right of the command.
 */
void	join_right_redirections_to_cmd(t_token_node **token)
{
	if (*token && ((*token)->token.type == BUILTIN_CMD
			|| (*token)->token.type == SIMPLE_CMD))
	{
		if ((*token)->next && (*token)->next->token.type == REDIRECTION)
		{
			if ((*token)->next->next
				&& (*token)->next->next->token.type == REDIRECTION)
			{
				(*token)->left = (*token)->next;
				(*token)->right = (*token)->next->next;
				return ;
			}
			else
			{
				if (!(*token)->left)
					(*token)->left = (*token)->next;
				else
					(*token)->right = (*token)->next;
			}
		}
	}
}

/* Function: join_tokens_to_pipe
 * ------------------------------
 * Attaches command tokens to a pipe token in the binary tree.
 * 
 * token: A double pointer to the current token node, which should be a PIPE token.
 * first_pipe: A double pointer to the first PIPE token encountered.
 * 
 * This function attaches the command token on the left of the pipe to the pipe
 * and then attempts to attach the command token on the right of the pipe to the pipe.
 */
void	join_tokens_to_pipe(t_token_node **token, t_token_node **first_pipe)
{
	join_left_token_to_pipe(token, first_pipe);
	join_right_token_to_pipe(token);
}

/* Function: join_left_token_to_pipe
 * ----------------------------------
 * Attaches the left command token to a pipe token in the binary tree.
 * 
 * token: A double pointer to the current token node, which should be a PIPE token.
 * first_pipe: A double pointer to the first PIPE token encountered.
 * 
 * This function checks if the previous token is a command token (either BUILTIN_CMD
 * or SIMPLE_CMD). If so, it sets this command token as the left child of the current
 * PIPE token. It handles the case where there are multiple pipes by setting the
 * appropriate command token as the left child.
 */
void	join_left_token_to_pipe(t_token_node **token, t_token_node **first_pipe)
{
	if ((*token)->prev && ((*token)->prev->token.type == BUILTIN_CMD
			|| (*token)->prev->token.type == SIMPLE_CMD))
	{
		if (!*first_pipe)
		{
			*first_pipe = *token;
			(*token)->left = (*token)->prev;
		}
		else
		{
			if ((*token)->prev->prev
				&& (*token)->prev->prev->token.type == PIPE)
				(*token)->left = (*token)->prev->prev;
		}
	}
}