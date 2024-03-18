/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init_single_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:28:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/18 14:02:54 by sfrankie         ###   ########.fr       */
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
		token.in = open(file_name, O_RDONLY);
		if (token.in == -1 && ft_strlen(token.t_value.single_ptr) == 1
			&& token.t_value.single_ptr[0] == '<')
		{
			ft_printf("bash: %s: No such file or directory\n", file_name);
			token.type = WRONG_FD;
			printf("%i\n", token.in);
		}
		token.type = REDIRECTION;
	}
	return (token);
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
