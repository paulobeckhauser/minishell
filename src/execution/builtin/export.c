/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:47:36 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: is_export_command
 * ----------------------------
 * Checks if the given command is the 'export' command.
 * 
 * command: A pointer to an array of strings representing the command and its arguments.
 * 
 * Returns 1 (true) if the first string in the command array is "export", otherwise returns 0 (false).
 */
int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

/* Function: execute_export_command
 * ---------------------------------
 * Executes the 'export' command based on the provided arguments.
 * 
 * structure: A pointer to the main structure containing environment variables, command arguments, and other data.
 * 
 * If the 'export' command is issued without any arguments (i.e., the second string in the command array is NULL),
 * it calls the export_without_args function to display all environment variables. Otherwise, it calls the
 * export_with_args function to process the arguments provided with the 'export' command.
 */
void	execute_export_command(t_info *structure)
{
	if (structure->table->arr[1] == NULL)
		export_without_args(structure); // Calls function to handle 'export' without arguments
	else
		export_with_args(structure); // Calls function to handle 'export' with arguments
}