/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:28:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 14:35:26 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	init_error_token(void)
{
	t_token	token;

	token.type = WRONG;
	token.t_value.single_ptr = NULL;
	return (token);
}

t_token init_pipe_token(t_input *input)
{
	t_token	token;

	token.type = PIPE;
	token.t_value.single_ptr = "|";
	++input->pipe_count;
	return (token);
}
t_token	init_redirection_token(t_input *input)
{
	t_token	token;

	token.type = REDIRECTION;
	token.t_value.single_ptr = verify_redirection(input);
	return (token);
}

t_token	init_cmd_token(t_input *input)
{
	t_token	token;

	count_words(input);
	init_words_arr(input);
	if (!if_builtin_cmd(input->arr[0]))
		token = init_simple_cmd_token(input);
	else
		token = init_builtin_cmd_token(input);
	return (token);
}

t_token init_builtin_cmd_token(t_input *input)
{
	t_token	token;

	token.type = BUILTIN_CMD;
	token.t_value.double_ptr = input->arr;
	return (token);
}
