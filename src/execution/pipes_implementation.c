/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 16:00:28 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: free_pipe_structure
 * ------------------------------
 * Frees all allocated memory related to the pipe structure.
 * 
 * structure: The structure containing all pipe-related information.
 */
static void	free_pipe_structure(t_info *structure)
{
	free_2d_int_array(structure->fds_pipes);
	free_2d_array(structure->commands);
	free_2d_array(structure->path_commands);
	free(structure->path_env);
	free(structure->pid);
}

/* Function: close_fds_pipes_parent
 * ---------------------------------
 * Closes file descriptors in the parent process to avoid leaks.
 * 
 * structure: The structure containing all pipe-related information.
 * i: The index of the current command being executed.
 */
static void	close_fds_pipes_parent(t_info *structure, int i)
{
	if (i != 0)
		close(structure->fds_pipes[i - 1][0]);
	if (structure->table->next != NULL)
		close(structure->fds_pipes[i][1]);
}

/* Function: fork_and_execution
 * -----------------------------
 * Forks the current process and executes the child process or handles the parent process.
 * 
 * structure: The structure containing all pipe-related information.
 * i: The index of the current command being executed.
 */
static void	fork_and_execution(t_info *structure, int i)
{
	structure->pid[i] = fork();
	handle_child_key_combos();
	if (structure->pid[i] == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (structure->pid[i] == 0)
		execute_child_process(structure, i);
	else
		close_fds_pipes_parent(structure, i);
}

/* Function: pipeline_execution
 * -----------------------------
 * Executes the pipeline of commands using forks and pipes.
 * 
 * structure: The structure containing all pipe-related information.
 */
static void	pipeline_execution(t_info *structure)
{
	t_cmd	*head;
	int		i;
	int		status;
	pid_t	w_id;

	head = structure->table;
	i = 0;
	while (structure->table)
	{
		fork_and_execution(structure, i);
		i++;
		structure->table = structure->table->next;
	}
	structure->table = head;
	w_id = wait_child_processes(structure, &status);
	(void)w_id;
	free_pipe_structure(structure);
}

/* Function: pipes_implementation
 * -------------------------------
 * Main function to implement pipes in the shell.
 * 
 * structure: The structure containing all pipe-related information.
 */
void	pipes_implementation(t_info *structure)
{
	create_pipes(structure);
	structure->pid = (pid_t *)ft_calloc((structure->number_commands),
			sizeof(pid_t));
	if (structure->pid == NULL)
	{
		perror("Memory allocation failed\n");
		structure->last_exit_status = EXIT_FAILURE;
		return ;
	}
	pipeline_execution(structure);
}