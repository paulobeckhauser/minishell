/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:49:06 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/17 12:52:03 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void get_number_commands(t_info *structure)
{
    int number_commands;

	number_commands = 0;
	while(structure->table)
	{
		if (structure->table->arr[0])
			number_commands++;
		structure->table = structure->table->next;
	}
    structure->number_commands = number_commands;
    
}