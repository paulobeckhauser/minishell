/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_single_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:13:29 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:19:41 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_single_quote_checker_list
 * -----------------------------------------
 * Initializes a linked list to keep track of single-quoted strings in the command array.
 * 
 * prompt: Struct containing shell information.
 * 
 * This function creates a linked list where each node corresponds to a word in the
 * command array. It initializes each node with the index of the word and a boolean
 * indicating whether the word is within single quotes. This list is used to efficiently
 * track and update the single-quoted status of words as the shell processes commands.
 */
void	init_single_quote_checker_list(t_prompt *prompt)
{
	t_single_quote_checker	*checker;
	t_single_quote_checker	*head;
	int						i;

	i = 0;
	head = malloc(sizeof(t_single_quote_checker));
	if (!head)
		return ;
	checker = head;
	while (i < prompt->word_count)
	{
		checker->index = i;
		checker->single_quoted = false;
		if (i < prompt->word_count - 1)
		{
			checker->next = malloc(sizeof(t_single_quote_checker));
			if (!checker->next)
				return ;
			checker = checker->next;
		}
		else
			checker->next = NULL;
		i++;
	}
	prompt->checker = head;
}

/* Function: update_single_quote_status
 * -------------------------------------
 * Updates the single-quoted status of a word in the command array.
 * 
 * prompt: Struct containing shell information.
 * i: The index of the word in the command array whose status is to be updated.
 * 
 * This function iterates through the linked list of single_quote_checker nodes
 * until it finds the node corresponding to the given index. It then updates the
 * single_quoted boolean of that node to true, indicating that the word is within
 * single quotes. This is used when parsing the command array to correctly handle
 * words enclosed in single quotes.
 */
void	update_single_quote_status(t_prompt *prompt, int i)
{
	t_single_quote_checker	*head;

	head = prompt->checker;
	while (prompt->checker)
	{
		if (prompt->checker->index == i)
		{
			prompt->checker->single_quoted = true;
			prompt->checker = head;
			return ;
		}
		prompt->checker = prompt->checker->next;
	}
	prompt->checker = head;
}