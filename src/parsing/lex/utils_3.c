/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:27:18 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:21:49 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: find_next_token_to_print_in_err
 * -----------------------------------------
 * Finds the next token in the prompt message that would be relevant for printing
 * in an error message.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * 
 * Returns: A string representing the token that caused the error, or NULL if no
 * relevant token is found.
 * 
 * This function identifies the next token in the prompt message by calling
 * find_token and returns a string representation of the token if it is a PIPE or
 * REDIRECTION. For REDIRECTION, it further verifies the redirection by calling
 * verify_redirection. If the token is neither, it returns NULL.
 */
char	*find_next_token_to_print_in_err(t_prompt *prompt)
{
	t_type	type;

	type = find_token(prompt);
	if (type == PIPE)
		return ("|");
	else if (type == REDIRECTION)
		return (verify_redirection(prompt));
	else
		return (NULL);
}

/* Function: if_wrong_pipe_placement
 * ---------------------------------
 * Checks for incorrect placement of PIPE tokens in the token list.
 * 
 * head: A pointer to the head of the token list.
 * current: A pointer to the current token node in the list.
 * structure: A pointer to the structure containing shell information, including
 * the last exit status.
 * 
 * Returns: 1 if a PIPE token is incorrectly placed at the beginning or end of the
 * token list, indicating a syntax error. Otherwise, returns 0.
 * 
 * This function checks if a PIPE token is found at the beginning or end of the token
 * list, which would be a syntax error. If such an error is found, it sets the last
 * exit status to 2, frees the token list, prints an error message, and returns 1 to
 * indicate the error. Otherwise, it returns 0, indicating no syntax error with PIPE
 * placement.
 */
int	if_wrong_pipe_placement(t_token_node **head, t_token_node **current,
	t_info *structure)
{
	if ((*head && (*head)->token.type == PIPE)
		|| (*current && (*current)->token.type == PIPE))
	{
		structure->last_exit_status = 2;
		free_token_list_full(head);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}