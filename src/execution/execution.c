/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:54:35 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: preparation_for_execution
 * ------------------------------------
 * Prepares the shell for command execution.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function handles any key combinations that might affect the execution and
 * calculates the number of commands to be executed.
 */
static void	preparation_for_execution(t_info *structure)
{
	handle_key_combos_execution();
	get_number_commands(structure);
}

/* Function: pipeline_execution
 * -----------------------------
 * Executes a pipeline of commands.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function stores the commands and their paths, and then implements the pipes
 * between them for inter-process communication.
 */
static void	pipeline_execution(t_info *structure)
{
	store_commands(structure);
	store_path_commands(structure);
	pipes_implementation(structure);
}

/* Function: print_err_no_path
 * ----------------------------
 * Prints an error message for each command in the list if its path is not found.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function iterates over the list of commands and prints an error message for
 * each command indicating that the file or directory was not found. It also sets
 * the last exit status to indicate a command not found error.
 */
static void	print_err_no_path(t_info *structure)
{
	t_cmd	*head;

	head = structure->table;
	while (structure->table)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(structure->table->arr[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		structure->table = structure->table->next;
	}
	structure->table = head;
	structure->last_exit_status = EX_COMM_NOTFOUND;
}

/* Function: execution
 * -------------------
 * Executes the commands stored in the structure.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function checks if the command to be executed is a built-in command and if there
 * is only one command to execute. If so, it executes the built-in command directly.
 * Otherwise, it checks if the command's path is available. If not, it prints an error
 * message. If the path is available, it proceeds to execute the pipeline of commands.
 * 
 * Returns: Always returns true, indicating that the execution process has completed.
 */
bool	execution(t_info *structure)
{
	int		flag_cur_folder;
	char	cwd[PATH_MAX];

	flag_cur_folder = 0;
	structure->folder = getcwd(cwd, sizeof(cwd));
	preparation_for_execution(structure);
	if (structure->table->type == BUILTIN_CMD
		&& structure->number_commands == 1)
		builtin_execution(structure);
	else
	{
		flag_cur_folder = get_path_env(structure);
		if (flag_cur_folder == 0)
			print_err_no_path(structure);
		else
			pipeline_execution(structure);
	}
	return (true);
}