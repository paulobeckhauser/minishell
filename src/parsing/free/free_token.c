/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:57:44 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/23 19:02:26 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

static void	free_redirect_files(t_token_node *current)
{
	if (current->token.type == REDIRECTION)
	{
		if (current->token.in.file_name)
			free_double_arr(current->token.in.file_name);
		if (current->token.out.file_name)
		{
			if (current->token.out.trunc)
				free(current->token.out.trunc);
			free_double_arr(current->token.out.file_name);
		}
	}
}

static void	free_builtin_or_simpl_cmd(t_token_node *current)
{
	if ((current->token.type == BUILTIN_CMD
			|| current->token.type == SIMPLE_CMD) && current->token.word_val)
		free_double_arr(current->token.word_val);
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
		if (current->token.type == ERROR)
		{
			free(current);
			current = next;
		}
		free_redirect_files(current);
		free_builtin_or_simpl_cmd(current);
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}
