/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:49:40 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 21:04:07 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	free_prompt(t_prompt *prompt)
{
	free(prompt->start_ptr_save);
}

void	free_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_single_quote_checker_list(t_prompt *prompt)
{
	t_single_quote_checker	*current;
	t_single_quote_checker	*next;

	current = prompt->checker;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	prompt->checker = NULL;
}

void	free_tree(t_token_node *node)
{
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	free(node);
}

void	free_token_list(t_token_node **list)
{
	t_token_node	*current;
	t_token_node	*next;

	current = NULL;
	next = NULL;
	current = *list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}

void	free_token_list_full(t_token_node **list)
{
	t_token_node	*current;
	t_token_node	*next;

	current = NULL;
	next = NULL;
	current = *list;
	while (current != NULL)
	{
		if (current->token.out.trunc)
			free(current->token.out.trunc);
		if (current->token.word_val)
			free_double_arr(current->token.word_val);
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}

void	free_cmd_table(t_cmd **table)
{
	t_cmd	*current;
	t_cmd	*next;
	// int		i;

	current = *table;
	while (current)
	{
		next = current->next;
		if (current->in.file_name)
			free_double_arr(current->in.file_name);
		if (current->out.file_name)
			free_double_arr(current->out.file_name);
		if (current->out.trunc)
			free(current->out.trunc);
		if (current->arr)
			free_double_arr(current->arr);
		free(current);
		current = next;
	}
	*table = NULL;
}
