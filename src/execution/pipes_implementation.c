/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/21 16:48:27 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_pipe_structure(t_info *structure)
{
	free_2d_int_array(structure->fds_pipes);
	free_2d_array(structure->commands);
	free_2d_array(structure->path_commands);
	free(structure->path_env);
	free(structure->pid);
}

static void	close_fds_pipes_parent(t_info *structure, int i)
{
	if (i != 0)
		close(structure->fds_pipes[i - 1][0]);
	if (structure->table->next != NULL)
		close(structure->fds_pipes[i][1]);
}

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

void	pipes_implementation(t_info *structure)
{
	int		i;
	pid_t	w_id;
	t_cmd	*head;
	char	**current;
	int		status;

	create_pipes(structure);
	structure->pid = (pid_t *)ft_calloc((structure->number_commands),
			sizeof(pid_t));
	if (structure-> pid == NULL)
	{
		perror("Memory allocation failed\n");
		structure->last_exit_status = EXIT_FAILURE;
		return ;
	}
	current = structure->table->arr;
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
	free_pipe_structure(structure);
}
