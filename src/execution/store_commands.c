/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:17:51 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 10:02:24 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		while (current_table->arr[0][j])
		{
			j++;
		}
		structure->commands[i] = (char *)ft_calloc((j + 1), sizeof(char));
		i++;
		current_table = current_table->next;
	}
}

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
		while (current_table->arr[0][j])
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
