/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:54:34 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:28:32 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: print_syntax_token_error
 * -----------------------------------
 * Prints a syntax error message related to unexpected tokens.
 * 
 * prompt: A pointer to the prompt structure containing the error message.
 * 
 * If the error message in the prompt is empty, it prints a generic syntax error
 * message for an unexpected newline token. Otherwise, it prints a syntax error
 * message for the specific unexpected token found by calling
 * find_next_token_to_print_in_err.
 */
void	print_syntax_token_error(t_prompt *prompt)
{
	if (!*prompt->msg)
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
	else
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			find_next_token_to_print_in_err(prompt));
}

/* Function: print_heredoc_end_of_file
 * ------------------------------------
 * Prints a warning message for a heredoc that ends unexpectedly due to reaching
 * the end of file before finding the specified delimiter.
 * 
 * delimiter: The delimiter string that was expected to terminate the heredoc.
 * 
 * This function prints a warning message indicating that the heredoc was
 * delimited by the end-of-file (EOF) instead of finding the expected delimiter.
 */
void	print_heredoc_end_of_file(char *delimiter)
{
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file", 1);
	ft_putstr_fd(" (wanted `", 1);
	ft_putstr_fd(delimiter, 1);
	ft_putstr_fd("')\n", 1);
}