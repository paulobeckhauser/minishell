/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/11 17:57:02 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_input_data *input_data)
{
	lexer(input_data);
}

void	lexer(t_input_data *input_data)
{
	t_token_node	*list;

	init_symbols_and_whitespace_strings(input_data);
	default_display_with_history(input_data);
	list = init_token_list(input_data);
	if (!list)
		perror("Error initializing token list.");
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

t_token_node	*init_token_list(t_input_data *input_data)
{
	t_token_node	*node;
	t_token_node	*start_ptr;
	t_token_node	*current;
	int				i;

	start_ptr = NULL;
	current = NULL;
	i = 0;
	while (1)
	{
		node = malloc(sizeof(t_token_node));
		if (!node)
			return (NULL);
		node->token = init_token_struct(input_data);
		node->next = NULL;
		node->index = i++;
		if (node->token.type == WRONG)
		{
			free(node);
			break ;
		}
		if (!start_ptr)
		{
			start_ptr = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = current->next;
		}
	}
	return (start_ptr);
}

t_token	init_token_struct(t_input_data *input_data)
{
	t_type	type;
	t_token	token;
	t_token	error_token;

	error_token.type = WRONG;
	type = find_token(input_data);
	if (type == PIPE)
	{
		token.type = PIPE;
		token.t_value.single_ptr = "|";
	}
	else if (type == REDIRECTION)
	{
		token.type = REDIRECTION;
		token.t_value.single_ptr = verify_redirection(input_data);
	}
	else if (type == WORD)
	{
		count_words(input_data);
		init_words_arr(input_data);
		if (!builtin_cmd(input_data->arr[0]))
			token = make_simple_cmd(input_data);
		else
			token = make_builtin_cmd(input_data);
	}
	else
		token = error_token;
	if (type != WORD && type != REDIRECTION)
		input_data->input++;
	return (token);
}

t_type	find_token(t_input_data *input_data)
{
	t_type	type;

	if (input_data->start_ptr_save == NULL)
		input_data->start_ptr_save = input_data->input;
	input_data->word_count = 0;
	skip_whitespaces(input_data);
	if (*input_data->input == 0)
		type = WRONG;
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
	}
	input_data->arr[i][y] = 0;
	input_data->arr[i + 1] = NULL;
}

t_token	make_simple_cmd(t_input_data *input_data)
{
	t_token	token;

	token.type = SIMPLE_COMMAND;
	token.t_value.double_ptr = input_data->arr;
	return (token);
}

t_token make_builtin_cmd(t_input_data *input_data)
{
	t_token	token;

	token.type = BUILTIN_COMMAND;
	token.t_value.double_ptr = input_data->arr;
	return (token);
}
