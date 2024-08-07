/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_type_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:35:11 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 16:08:54 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_builtin_cmd_token
 * --------------------------------
 * Initializes a token for a builtin command with default I/O settings.
 * 
 * prompt: A pointer to the t_prompt structure containing the command and arguments.
 * 
 * Returns: An initialized t_token structure for a builtin command.
 */
t_token	init_builtin_cmd_token(t_prompt *prompt)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false; 
	token.out.fd = 1;
	token.out.file_name = NULL; 
	token.type = BUILTIN_CMD;
	token.val = NULL; 
	token.word_val = prompt->arr; 
	token.last_redirection = false;
	return (token);
}

/* Function: init_simple_cmd_token
 * -------------------------------
 * Initializes a token for a simple command with default I/O settings.
 * 
 * prompt: A pointer to the t_prompt structure containing the command and arguments.
 * 
 * Returns: An initialized t_token structure for a simple command.
 */
t_token	init_simple_cmd_token(t_prompt *prompt)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL; 
	token.in.heredoc = false; 
	token.out.fd = 1;
	token.out.file_name = NULL; 
	token.type = SIMPLE_CMD; 
	token.val = NULL; 
	token.word_val = prompt->arr; 
	token.last_redirection = false;
	return (token);
}