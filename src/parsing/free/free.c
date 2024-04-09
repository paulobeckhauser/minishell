/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:49:40 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/09 16:04:27 by pabeckha         ###   ########.fr       */
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

void	free_token_list(t_token_node **list)
{
	t_token_node	*current;
	t_token_node	*next;

	current = *list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}

void	free_cmd_table(t_info *structure)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = structure->table;
	while (current != NULL)
	{
		next = current->next;
		if (current->arr != NULL)
		{
			i = 0;
			while (current->arr[i] != NULL)
			{
				free(current->arr[i]);
				i++;
			}
			free(current->arr);
		}
		free(current);
		current = next;
	}
	structure->table = NULL;
}
