/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:49:06 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 13:17:14 by pabeckha         ###   ########.fr       */
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
		if (current_table->arr[0])
			number_commands++;
		current_table = current_table->next;
	}
	structure->number_commands = number_commands;
}
