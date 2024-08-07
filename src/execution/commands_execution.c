/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:34:03 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:53:13 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: handle_no_redirection
 * -------------------------------
 * Handles the case where there is no redirection for a command.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * i: The index of the current command being executed.
 * 
 * This function manages file descriptors for commands without redirection. It sets up
 * the standard input and output based on the position of the command in the pipeline.
 */
static void	handle_no_redirection(t_info *structure, int i)
{
	if (structure->table->out.fd == 0)
	{
		if (i != 0)
		{
			close(structure->fds_pipes[i - 1][1]);
			dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
		}
		if (structure->table->next != NULL)
		{
			close(structure->fds_pipes[i][0]);
			dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
		}
	}
	else
	{
		if (i != 0)
		{
			close(structure->fds_pipes[i - 1][1]);
			dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
		}
	}
}

/* Function: handle_redirection
 * ----------------------------
 * Handles the case where there is redirection for a command.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * i: The index of the current command being executed.
 * 
 * This function manages file descriptors for commands with redirection. It sets up
 * the standard input and output based on the position of the command in the pipeline
 * and the specified redirections.
 */
static void	handle_redirection(t_info *structure, int i)
{
	if (structure->table->out.fd == 0)
	{
		if (i != 0)
		{
			dup2(structure->fds_pipes[i - 1][1], STDIN_FILENO);
			close(structure->fds_pipes[i - 1][0]);
		}
		if (structure->table->next != NULL)
		{
			dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
			close(structure->fds_pipes[i][1]);
		}
	}
}

/* Function: input_redirections
 * ----------------------------
 * Manages input redirections for a command.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * i: The index of the current command being executed.
 * 
 * This function decides whether to handle redirections or not based on the command's
 * input file descriptor and then calls the appropriate function.
 */
static void	input_redirections(t_info *structure, int i)
{
	if (structure->table->in.fd == 0)
		handle_no_redirection(structure, i);
	else if (structure->table->in.fd > 0)
		handle_redirection(structure, i);
}

/* Function: commands_execution
 * -----------------------------
 * Executes a command.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * i: The index of the current command being executed.
 * 
 * This function executes a command. If the command is a builtin, it calls the function
 * for executing builtin commands. Otherwise, it attempts to execute the command using
 * execve and checks the command's path if execve fails.
 */
void	commands_execution(t_info *structure, int i)
{
	if (structure->table->type == BUILTIN_CMD)
	{
		builtin_execution(structure);
		exit(EXIT_SUCCESS);
	}
	{
		if (execve(structure->path_commands[i], structure->table->arr,
				structure->envp) == -1)
			check_path(structure->path_commands[i], structure->table->arr[0]);
	}
}

/* Function: execute_child_process
 * --------------------------------
 * Executes a child process for a command.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * i: The index of the current command being executed.
 * 
 * This function prepares a child process for execution. It opens necessary files,
 * manages input redirections, closes unused file descriptors, and then calls the
 * function to execute the command.
 */
void	execute_child_process(t_info *structure, int i)
{
	int	j;

	if (!open_files(structure->table))
		exit(EXIT_FAILURE);
	input_redirections(structure, i);
	j = 0;
	while (j < structure->number_commands - 1)
	{
		close(structure->fds_pipes[j][0]);
		close(structure->fds_pipes[j][1]);
		j++;
	}
	commands_execution(structure, i);
}