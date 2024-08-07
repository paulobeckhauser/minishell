/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:45:10 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: is_exit_command
 * -------------------------
 * Checks if the first command argument is "exit".
 * 
 * command: The array of command arguments.
 * 
 * Returns 1 if the first command argument is "exit", otherwise returns 0.
 * This function is used to determine if the command being processed is an exit command.
 */
int	is_exit_command(char **command)
{
	return (ft_strcmp(command[0], "exit") == 0);
}

/* Function: execute_exit_command
 * -------------------------------
 * Executes the exit command based on the number of arguments provided.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * Counts the number of arguments in the command. If there is only one argument,
 * it calls exit_1_arg to handle the exit command with no additional arguments.
 * If there are two arguments, it calls exit_2_args to handle the exit command
 * with one additional argument, which should be a numeric value. If there are
 * more than two arguments, it calls exit_more_args to handle the case where
 * too many arguments are provided for the exit command.
 */
void	execute_exit_command(t_info *structure)
{
	int	nb_args;

	nb_args = 0;
	while (structure->table->arr[nb_args])
		nb_args++;
	if (nb_args == 1)
		exit_1_arg(structure);
	else if (nb_args == 2)
		exit_2_args(structure);
	else
		exit_more_args(structure);
}