/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init_token_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:28:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/05 19:45:18 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	init_end_token(void)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false;
	token.out.fd = 1;
	token.out.file_name = NULL;
	token.type = END;
	token.t_value.single_ptr = NULL;
	token.last_redirection = false;
	return (token);
}

t_token	init_error_token(void)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false;
	token.out.fd = 1;
	token.out.file_name = NULL;
	token.type = ERROR;
	token.t_value.single_ptr = NULL;
	token.last_redirection = false;
	return (token);
}

t_token init_pipe_token(t_prompt *prompt)
{
	t_token	token;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false;
	token.out.fd = 1;
	token.out.file_name = NULL;
	token.type = PIPE;
	token.t_value.single_ptr = "|";
	token.last_redirection = false;
	++prompt->pipe_count;
	return (token);
}

t_token	init_redirection_token(t_prompt *prompt)
{
	t_token	token;
	char	*file_name;

	token.in.fd = 0;
	token.in.file_name = NULL;
	token.in.heredoc = false;
	token.out.fd = 1;
	token.out.file_name = NULL;
	token.t_value.single_ptr = verify_redirection(prompt);
	token.last_redirection = false;
	file_name = fetch_file_name(prompt);
	if (!file_name)
	{
		token = init_error_token();
		print_syntax_token_error(prompt);
	}
	else if (token.t_value.single_ptr[0] == '<' && ft_strlen(token.t_value.single_ptr) == 1)
		init_in_redirection(&token, file_name);
	else if (token.t_value.single_ptr[0] == '<' && token.t_value.single_ptr[1] == '<')
		init_heredoc_in_redirection(&token, file_name, prompt);
	else if (token.t_value.single_ptr[0] == '>' && ft_strlen(token.t_value.single_ptr) == 1)
		init_truncate_out_redirection(&token, file_name);
	else if (token.t_value.single_ptr[0] == '>' && token.t_value.single_ptr[1] == '>')
		init_append_out_redirection(&token, file_name);
	g_signal = 0;
	return (token);

}

t_token	init_cmd_token(t_prompt *prompt)
{
	t_token	token;
	
	count_words(prompt);
	init_words_arr(prompt);
	verify_dollar(prompt);
	if (!if_builtin_cmd(prompt->arr[0]))
		token = init_simple_cmd_token(prompt);
	else
		token = init_builtin_cmd_token(prompt);
	return (token);
}

void	verify_dollar(t_prompt *prompt)
{
	int		i;
	int		y;
	char	*dollar_word;
	i = 0;
	while (prompt->arr[i])
	{
		if (ft_strchr(prompt->arr[i], '$'))
		{
			dollar_word = find_dollar_word(prompt, prompt->arr[i]);
			
		}
	}
}

char	*find_dollar_word(t_prompt *prompt, char *str)
{
	int		len;
	int		i;
	char	*dollar_word;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
			break ;
	}
	len = 0;
	while (str[len] && ft_strchr(prompt->whitespace, str[len]) && str[len] != '$')
		len++;
	dollar_word = malloc(len + 1);
	if (!dollar_word)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (ft_strchr(prompt->whitespace, *str) || *str == '$')
			break ;
		dollar_word[i++] = *str++;
	}
	dollar_word[i] = 0;
	return (dollar_word);
}