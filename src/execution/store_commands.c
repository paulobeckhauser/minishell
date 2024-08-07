/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:17:51 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/16 12:33:37 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: allocate_memory_commands
 * ----------------------------------
 * Allocates memory for the commands array within the t_info structure.
 * This array will store the first command from each command table.
 * 
 * structure: A pointer to the t_info structure containing the command tables.
 */
static void	allocate_memory_commands(t_info *structure)
{
	t_cmd	*current_table;
	int		j;
	int		i;

	i = 0;
	current_table = structure->table;
	structure->commands = (char **)ft_calloc((structure->number_commands + 1),
			sizeof(char *));
	if (!structure->commands)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	while (current_table)
	{
		j = 0;
		while (current_table->arr && current_table->arr[0]
			&& current_table->arr[0][j])
		{
			j++;
		}
		structure->commands[i] = (char *)ft_calloc((j + 1), sizeof(char));
		i++;
		current_table = current_table->next;
	}
}

/* Function: store_commands
 * ------------------------
 * Copies the first command from each command table into the commands array
 * within the t_info structure.
 * 
 * structure: A pointer to the t_info structure containing the command tables.
 */
void	store_commands(t_info *structure)
{
	t_cmd	*current_table;
	int		i;
	int		j;
	int		count;

	allocate_memory_commands(structure);
	current_table = structure->table;
	i = 0;
	while (current_table)
	{
		j = 0;
		count = 0;
		while (current_table->arr && current_table->arr[0]
			&& current_table->arr[0][j])
		{
			count++;
			j++;
		}
		ft_strlcpy(structure->commands[i], current_table->arr[0],
			ft_strlen(current_table->arr[0]) + 1);
		i++;
		current_table = current_table->next;
	}
}