/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:59:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:51:34 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: builtin_execution
 * ---------------------------
 * Executes the appropriate builtin command based on the user's input.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function first attempts to open any files specified in the command. If this fails,
 * it sets the last exit status to failure and returns. It then checks which builtin command
 * is being called by the user and calls the appropriate function to execute it. For the 'env'
 * command, it also checks if the PATH environment variable is set. If not, it prints an error
 * message and sets the last exit status to 127. If the command is 'exit', it calls the function
 * to execute 'exit'.
 */
void	builtin_execution(t_info *structure)
{
	if (!open_files(structure->table))
	{
		structure->last_exit_status = EXIT_FAILURE;
		return ;
	}
	if (is_cd_command(structure->table->arr))
		execute_cd_command(structure);
	if (is_pwd_command(structure->table->arr))
		execute_pwd_command(structure->table->arr);
	if (is_echo_command(structure->table->arr))
		execute_echo_command(structure);
	if (is_export_command(structure->table->arr))
		execute_export_command(structure);
	if (is_unset_command(structure->table->arr))
		execute_unset_command(structure);
	if (is_env_command(structure->table->arr) && get_path_env(structure) != 0)
		execute_env_command(structure);
	else if (is_env_command(structure->table->arr)
		&& get_path_env(structure) == 0)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		structure->last_exit_status = 127;
	}
	if (is_exit_command(structure->table->arr))
		execute_exit_command(structure);
}