/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init_token_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:28:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/06 20:30:45 by sfrankie         ###   ########.fr       */
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

t_token	init_cmd_token(t_info *structure, t_prompt *prompt)
{
	t_token	token;
	
	count_words(prompt);
	init_words_arr(prompt);
	verify_dollar(structure, prompt);
	if (!if_builtin_cmd(prompt->arr[0]))
		token = init_simple_cmd_token(prompt);
	else
		token = init_builtin_cmd_token(prompt);
	return (token);
}

void	verify_dollar(t_info *structure, t_prompt *prompt)
{
	int		i;
	int		y;
	char	*dollar_word;
	char	*word_replacement;

	i = 0;
	while (prompt->arr[i])
	{
		while (ft_strchr(prompt->arr[i], '$'))
		{
			dollar_word = find_dollar_word(prompt, prompt->arr[i]);
			word_replacement = replace_dollar_word(structure, dollar_word);
			if (!word_replacement)
				word_replacement  = "";
			replace_words_in_arr(prompt, i, dollar_word, word_replacement);
		}
		i++;
	}
}

char	*find_dollar_word(t_prompt *prompt, char *str)
{
	int		len;
	int		i;
	char	*dollar_word;

	while (*str)
	{
		if (*str++ == '$')
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

char	*replace_dollar_word(t_info *structure, char *str)
{
	char	*word_replacement;
	char	*str_temp;
	int 	i;

	i = 0;
	while(structure->envp_export[i])
	{
		str_temp = allocate_str_temp(structure, str_temp, i);
		str_temp = save_str_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, str) == 0)
			return (extract_dollar_value(structure->envp_export[i]));
		i++;
	}
	return (NULL);
}

char	*extract_dollar_value(char *str)
{
	char	*word_replacement;
	char	*start_ptr_save;

	while (*str)
	{
		if (*str++ == '=')
			break ;
	}
	word_replacement = malloc(ft_strlen(str) + 1);
	if (!word_replacement)
		return (NULL);
	start_ptr_save = word_replacement;
	while (*str)
		*word_replacement++ = *str++;
	*word_replacement = 0;
	word_replacement = start_ptr_save;
	return (word_replacement);
}

void	replace_words_in_arr(t_prompt *prompt, int i, char *dollar_word, char *replacement)
{
    char	*new_str;
    char	*before_dollar;
    char	*after_dollar;
    int		dollar_word_len;
    int		y;

    dollar_word = ft_strjoin("$", dollar_word);
    dollar_word_len = ft_strlen(dollar_word);
    y = 0;
    while (prompt->arr[i][y])
    {
        if (ft_strncmp(prompt->arr[i] + y, dollar_word, dollar_word_len) == 0)
        {
            before_dollar = ft_substr(prompt->arr[i], 0, y - 1);
            after_dollar = ft_substr(prompt->arr[i], y + dollar_word_len, ft_strlen(prompt->arr[i]) - y - dollar_word_len);

            new_str = malloc(ft_strlen(before_dollar) + ft_strlen(replacement) + ft_strlen(after_dollar) + 1);
            ft_strlcpy(new_str, before_dollar, ft_strlen(before_dollar) + 1);
            ft_strlcat(new_str, replacement, ft_strlen(before_dollar) + ft_strlen(replacement) + 1);
            ft_strlcat(new_str, after_dollar, ft_strlen(before_dollar) + ft_strlen(replacement) + ft_strlen(after_dollar) + 1);

            free(prompt->arr[i]);
            prompt->arr[i] = new_str;

            free(before_dollar);
            free(after_dollar);

            return ;
        }
        else
            y++;
    }
}