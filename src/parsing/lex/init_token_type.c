/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:28:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:09:59 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_end_token
 * -------------------------
 * Initializes a token of type END.
 * This function sets up a token to represent the end of input or command sequence.
 * 
 * Returns: A token with type set to END and default I/O redirections.
 */
t_token	init_end_token(void)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false;
	token.out.fd = 1;
	token.out.file_name = NULL;
	token.type = END;
	token.val = NULL;
	token.word_val = NULL;
	token.last_redirection = false;
	return (token);
}

/* Function: init_error_token
 * ---------------------------
 * Initializes a token of type ERROR.
 * This function prepares a token to indicate an error in parsing or execution.
 * 
 * Returns: A token with type set to ERROR and default I/O redirections.
 */
t_token	init_error_token(void)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false;
	token.out.fd = 1;
	token.out.file_name = NULL;
	token.out.trunc = NULL;
	token.type = ERROR;
	token.val = NULL;
	token.word_val = NULL;
	token.last_redirection = false;
	return (token);
}

/* Function: init_pipe_token
 * --------------------------
 * Initializes a token of type PIPE.
 * This function sets up a token to represent a pipe ('|') in the command sequence.
 * 
 * prompt: The current command prompt context, used to increment the pipe count.
 * 
 * Returns: A token with type set to PIPE.
 */
t_token	init_pipe_token(t_prompt *prompt)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false;
	token.out.fd = 1;
	token.out.file_name = NULL;
	token.type = PIPE;
	token.val = "|";
	token.word_val = NULL;
	token.last_redirection = false;
	++prompt->pipe_count;
	return (token);
}

/* Function: init_redirection_token
 * ---------------------------------
 * Initializes a token of type REDIRECTION.
 * This function sets up a token to represent a redirection ('<', '<<', '>', '>>').
 * It determines the specific type of redirection based on the input and initializes accordingly.
 * 
 * prompt: The current command prompt context, used for fetching file names and other operations.
 * 
 * Returns: A token with type set to the specific redirection type.
 */
t_token	init_redirection_token(t_prompt *prompt)
{
	t_token	token;
	char	*file_name;

	init_primary_redirection_vars(&token, prompt);
	file_name = fetch_file_name(prompt);
	if (!file_name)
	{
		token = init_error_token();
		print_syntax_token_error(prompt);
	}
	else if (token.val[0] == '<'
		&& ft_strlen(token.val) == 1)
		init_in_redirection(&token, file_name, prompt);
	else if (token.val[0] == '<'
		&& token.val[1] == '<')
		init_heredoc_in_redirection(&token, file_name);
	else if (token.val[0] == '>'
		&& ft_strlen(token.val) == 1)
		init_truncate_out_redirection(&token, file_name, prompt);
	else if (token.val[0] == '>'
		&& token.val[1] == '>')
		init_append_out_redirection(&token, file_name, prompt);
	return (token);
}

/* Function: init_cmd_token
 * -------------------------
 * Initializes a token of type CMD (Command).
 * This function sets up a token to represent a command, determining if it's a built-in or a simple command.
 * 
 * structure: The current execution context structure.
 * prompt: The current command prompt context.
 * 
 * Returns: A token with type set to CMD, either built-in or simple based on the command.
 */
t_token	init_cmd_token(t_info *structure, t_prompt *prompt)
{
	t_token	token;

	count_words(prompt);
	init_words_arr(prompt);
	if (!verify_dollar(structure, prompt))
	{
		token.type = END;
		return (token);
	}
	if (!prompt->arr[0])
	{
		token.type = END;
		return (token);
	}
	if (!if_builtin_cmd(prompt->arr[0]))
		token = init_simple_cmd_token(prompt);
	else
		token = init_builtin_cmd_token(prompt);
	return (token);
}