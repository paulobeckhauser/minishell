/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/09 16:27:39 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer(t_input_data *input_data)
{
	init_symbols_and_whitespace_strings(input_data);
	default_display_with_history(input_data);
	init_token_struct(input_data);
	input_data->input = input_data->start_ptr_save;
	free(input_data->buf);
	free(input_data->input);
}

// Display current directory + prompt for user + addhistory for previous
// prompts, most probably this function will be changed or deleted 
// for sure it will be moved to other file (SZYMON)
void	default_display_with_history(t_input_data *input_data)
{
	input_data->buf = getcwd(NULL, 0);
	if (input_data->buf == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	input_data->buf = ft_strjoin(input_data->buf, "$ ");
	input_data->input = readline(input_data->buf);
	add_history(input_data->input);
}

void	init_token_struct(t_input_data *input_data)
{
	t_type	type;
	t_token	token;

	type = find_token(input_data);
	if (type == PIPE)
	{
		token.type = PIPE;
		token.value = "|";
		ft_printf("Found token PIPE: %s\n", token.value);
	}
	else if (type == REDIRECTION)
	{
		token.type = REDIRECTION;
		token.value = verify_redirection(input_data);
		ft_printf("Found token REDIRECTION: %s\n", token.value);
	}
	else if (type == WORD)
	{
		count_words(input_data);
		init_words_arr(input_data);
		if (!builtin_cmd())
			make_simple_cmd();
	}
}

t_type	find_token(t_input_data *input_data)
{
	t_type	type;

	input_data->start_ptr_save = input_data->input;
	input_data->word_count = 0;
	skip_whitespaces(input_data);
	if (*input_data->input == 0)
		return (0);
	if (ft_strchr(input_data->symbols, *input_data->input))
	{
		if (*input_data->input == '|' && *(input_data->input + 1) != '|')
			type = PIPE;
		else if (*input_data->input == '<' || *input_data->input == '>')
			type = REDIRECTION;
	}
	else
		type = WORD;
	return (type);
}

void	count_words(t_input_data *input_data)
{
	char	*start_ptr_save;

	start_ptr_save = input_data->input;
	input_data->word_count = 0;
	while (!ft_strchr(input_data->symbols, *input_data->input)
		&& *input_data->input)
	{
		if (ft_strchr(input_data->whitespace, *input_data->input))
		{
			skip_whitespaces(input_data);
			if (*input_data->input)
				input_data->word_count++;
		}
		else
			input_data->input++;
	}
	if (*input_data->input == 0)
		input_data->word_count++;
	input_data->input = start_ptr_save;
}

void	init_words_arr(t_input_data *input_data)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	input_data->arr = malloc((input_data->word_count + 1) * sizeof(char *));
	if (!input_data->arr)
		return ;
	input_data->arr[i] = malloc(get_word_length(input_data) + 1);
	if (!input_data->arr[i])
		return ;
	while (!ft_strchr(input_data->symbols, *input_data->input)
		&& *input_data->input)
	{
		if (ft_strchr(input_data->whitespace, *input_data->input))
		{
			skip_whitespaces(input_data);
			input_data->arr[i][y] = 0;
			if (*input_data->input == 0
				|| ft_strchr(input_data->symbols, *input_data->input))
				break ;
			i++;
			input_data->arr[i] = malloc(get_word_length(input_data) + 1);
			if (!input_data->arr[i])
				return ;
			y = 0;
		}
		else
			input_data->arr[i][y++] = *input_data->input++;
	input_data->arr[i][y] = 0;
	input_data->arr[i + 1] = NULL;
	}
}
