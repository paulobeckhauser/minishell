/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:43:51 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/18 15:02:35 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_node	*init_token_list(t_prompt *prompt)
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
		list = init_token_node(prompt, i++);
		if (!list)
			return (NULL);
		if (list->token.type == END)
		{
			free(list);
			break ;
		}
		add_node_to_list(&head, &current, list);
	}
	prompt->token_count = i;
	return (head);
}

t_token_node	*init_token_node(t_prompt *prompt, int index)
{
	t_token_node	*node;

	node = ft_calloc(1, sizeof(t_token_node));
	if (!node)
		return (NULL);
	node->token = init_token_struct(prompt);
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

t_token	init_token_struct(t_prompt *prompt)
{
	t_type	type;
	t_token	token;

	type = find_token(prompt);
	if (type == PIPE)
		token = init_pipe_token(prompt);
	else if (type == REDIRECTION)
		token = init_redirection_token(prompt);
	else if (type == WORD)
		token = init_cmd_token(prompt);
	else
		token = init_error_token();
	if (type != WORD && type != REDIRECTION)
		prompt->msg++;
	return (token);
}

t_type	find_token(t_prompt *prompt)
{
	t_type	type;

	if (prompt->start_ptr_save == NULL)
		prompt->start_ptr_save = prompt->msg;
	prompt->word_count = 0;
	skip_whitespaces(prompt);
	if (*prompt->msg == 0)
		type = END;
	if (ft_strchr(prompt->symbols, *prompt->msg))
	{
		if (*prompt->msg == '|' && *(prompt->msg + 1) != '|')
			type = PIPE;
		else if (*prompt->msg == '<' || *prompt->msg == '>')
			type = REDIRECTION;
	}
	else
		type = WORD;
	return (type);
}
