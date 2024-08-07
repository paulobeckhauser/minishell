/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:03:28 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:53:41 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: create_child_processes
 * ---------------------------------
 * Creates child processes for each command in a pipeline.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function iterates over the number of commands to be executed. For each command,
 * it forks a new process. In the child process, it sets up the standard input and output
 * for piping between commands, if necessary. Then, it attempts to execute the command
 * using execve. The parent process continues to the next command without waiting.
 */
void	create_child_processes(t_info *structure)
{
	int	i;

	// Allocate memory for storing child process IDs
	structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1),
			sizeof(pid_t));
	i = 0;
	while (i < structure->number_commands)
	{
		// Fork a new process for each command
		structure->pid[i] = fork();
		if (structure->pid[i] == 0) // Child process
		{
			// Set up input from the previous command, if not the first command
			if (i != 0)
			{
				dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
				close(structure->fds_pipes[i - 1][0]);
			}
			// Set up output to the next command, if not the last command
			if (i != structure->number_commands - 1)
			{
				dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
				close(structure->fds_pipes[i][1]);
			}
			// Attempt to execute the command
			execve(structure->path_commands[i], structure->table->arr,
				structure->envp);
		}
		i++;
	}
}