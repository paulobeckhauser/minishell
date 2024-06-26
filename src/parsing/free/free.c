/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:49:40 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 18:58:43 by pabeckha         ###   ########.fr       */
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

void	free_cmd_table(t_cmd **table)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *table;
	while (current)
	{
		next = current->next;
		if (current->in.file_name)
			free_double_arr(current->in.file_name);
		if (current->out.file_name)
			free_double_arr(current->out.file_name);
		if (current->out.file_name && current->out.trunc)
			free(current->out.trunc);
		if (current->arr)
			free_double_arr(current->arr);
		free(current);
		current = next;
	}
	*table = NULL;
}
