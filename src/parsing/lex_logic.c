/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:43:51 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 14:34:33 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_node	*init_token_list(t_input *input)
{
	t_token_node	*list;
	t_token_node	*head;
	t_token_node	*current;
	int				i;

	head = NULL;
	current = NULL;
	i = 0;
	while (1)
	{
		list = init_token_node(input, i++);
		if (!list)
			return (NULL);
		if (list->token.type == WRONG)
		{
			free(list);
			break ;
		}
		add_node_to_list(&head, &current, list);
	}
	input->token_count = i;
	return (head);
}

t_token_node	*init_token_node(t_input *input, int index)
{
	t_token_node	*node;

	node = ft_calloc(1, sizeof(t_token_node));
	if (!node)
		return (NULL);
	node->token = init_token_struct(input);
	node->next = NULL;
	node->index = index;
	return (node);
}

void	add_node_to_list(t_token_node **head, t_token_node **current,
	t_token_node *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = (*current)->next;
	}
}

t_token	init_token_struct(t_input *input)
{
	t_type	type;
	t_token	token;

	type = find_token(input);
	if (type == PIPE)
		token = init_pipe_token(input);
	else if (type == REDIRECTION)
		token = init_redirection_token(input);
	else if (type == WORD)
		token = init_cmd_token(input);
	else
		token = init_error_token();
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
