/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init_single_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:28:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/18 20:51:33 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	init_error_token(void)
{
	t_token	token;

	token.type = END;
	token.t_value.single_ptr = NULL;
	return (token);
}

t_token init_pipe_token(t_prompt *prompt)
{
	t_token	token;

	token.type = PIPE;
	token.t_value.single_ptr = "|";
	++prompt->pipe_count;
	return (token);
}

t_token	init_redirection_token(t_prompt *prompt)
{
	t_token	token;
	char	*file_name;

	token.t_value.single_ptr = verify_redirection(prompt);
	file_name = fetch_file_name(prompt);
	if (!file_name)
	{
		if (!*prompt->msg)
			ft_printf("bash: syntax error near unexpected token `newline'\n");
		else
			ft_printf("bash: syntax error near unexpected token `%s'\n",
				find_next_token_to_print_in_err(prompt));
		token.type = END;
	}
	else
	{
		if ()
		{
			token.in = init_in_struct(&token, file_name);
			token.type = REDIRECTION;
		}
		
	}
	return (token);
}

t_in	init_in_struct(t_token *token, char *file_name)
{
	t_in	in;

	in.redirect = true;
	in.fd = open(file_name, O_RDONLY);
	if (in.fd == -1 && ft_strlen(token->t_value.single_ptr) == 1
		&& token->t_value.single_ptr[0] == '<')
		in.file_name = file_name;
	else
		in.file_name = NULL;   
	return (in);
}

t_token	init_cmd_token(t_prompt *prompt)
{
	t_token	token;

	count_words(prompt);
	init_words_arr(prompt);
	if (!if_builtin_cmd(prompt->arr[0]))
		token = init_simple_cmd_token(prompt);
	else
		token = init_builtin_cmd_token(prompt);
	return (token);
}

t_token init_builtin_cmd_token(t_prompt *prompt)
{
	t_token	token;

	token.type = BUILTIN_CMD;
	token.t_value.double_ptr = prompt->arr;
	return (token);
}
