/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_single_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:13:29 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/22 18:40:30 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
