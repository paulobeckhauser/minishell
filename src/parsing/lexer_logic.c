/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:43:51 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 13:14:35 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_node	*init_token_list(t_input *input)
{
	t_token_node	*node;
	t_token_node	*start_ptr_save;
	t_token_node	*current;
	int				i;

	start_ptr_save = NULL;
	current = NULL;
	i = 0;
	while (1)
	{
		node = ft_calloc(1, sizeof(t_token_node));
		if (!node)
			return (NULL);
		node->token = init_token_struct(input);
		node->next = NULL;
		node->index = i++;
		if (node->token.type == WRONG)
		{
			free(node);
			break ;
		}
		if (!start_ptr_save)
		{
			start_ptr_save = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = current->next;
		}
	}
	input->token_count = i;
	return (start_ptr_save);
}

t_token	init_token_struct(t_input *input)
{
	t_type	type;
	t_token	token;
	t_token	error_token;

	error_token.type = WRONG;
	type = find_token(input);
	if (type == PIPE)
	{
		token.type = PIPE;
		token.t_value.single_ptr = "|";
		++input->pipe_count;
	}
	else if (type == REDIRECTION)
	{
		token.type = REDIRECTION;
		token.t_value.single_ptr = verify_redirection(input);
	}
	else if (type == WORD)
	{
		count_words(input);
		init_words_arr(input);
		if (!if_builtin_cmd(input->arr[0]))
			token = init_simple_cmd_token(input);
		else
			token = init_builtin_cmd_token(input);
	}
	else
		token = error_token;
	if (type != WORD && type != REDIRECTION)
		input->input++;
	return (token);
}

t_type	find_token(t_input *input)
{
	t_type	type;

	if (input->start_ptr_save == NULL)
		input->start_ptr_save = input->input;
	input->word_count = 0;
	skip_whitespaces(input);
	if (*input->input == 0)
		type = WRONG;
	if (ft_strchr(input->symbols, *input->input))
	{
		if (*input->input == '|' && *(input->input + 1) != '|')
			type = PIPE;
		else if (*input->input == '<' || *input->input == '>')
			type = REDIRECTION;
	}
	else
		type = WORD;
	return (type);
}
