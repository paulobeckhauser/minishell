/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:49:06 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/15 12:47:28 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_number_commands(t_info *structure)
{
	t_cmd	*current_table;
	int		number_commands;

	number_commands = 0;
	current_table = structure->table;
	while (current_table)
	{
		if (current_table->arr && current_table->arr[0])
			number_commands++;
		current_table = current_table->next;
	}
	structure->number_commands = number_commands;
}
