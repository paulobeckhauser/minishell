/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:49:06 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:55:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: get_number_commands
 * ------------------------------
 * Counts the number of commands in the command table.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function iterates through the command table linked list, counting each command
 * that has a non-empty first argument. It then updates the number_commands field in the
 * structure with the total count of commands.
 */
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