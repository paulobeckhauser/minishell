/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 18:52:01 by pabeckha         ###   ########.fr       */
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

static void	input_redirections(t_info *structure, int i)
{
	if (structure->table->in.fd == 0)
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
	else if (structure->table->in.fd > 0)
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

static void commands_execution(t_info *structure, int i)
{
    if (structure->table->type == BUILTIN_CMD)
    {
        builtin_execution(structure);
        exit(EXIT_SUCCESS);
    }
    {
        if (execve(structure->path_commands[i], structure->table->arr,
                structure->envp) == -1)
            check_path(structure->path_commands[i],
                structure->table->arr[0]);
    }
}

static void close_fds_pipes_parent(t_info *structure, int i)
{
    if (i != 0)
        close(structure->fds_pipes[i - 1][0]);
    if (structure->table->next != NULL)
        close(structure->fds_pipes[i][1]);
}

static void execute_child_process(t_info *structure, int i)
{
    int j;
    
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

void	pipes_implementation(t_info *structure)
{
	int		i;
	int		command_number;
	pid_t	w_id;
	t_cmd	*head;
	char	**current;
	int		status;

	create_pipes(structure);
	structure->pid = (pid_t *)ft_calloc((structure->number_commands),
			sizeof(pid_t));
	i = 0;
	current = structure->table->arr;
	command_number = 0;
	head = structure->table;
	while (structure->table)
	{
		command_number++;
		handle_child_key_combos();
		structure->pid[i] = fork();
		if (structure->pid[i] == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (structure->pid[i] == 0)
            execute_child_process(structure, i);
		else
            close_fds_pipes_parent(structure, i);
		i++;
		structure->table = structure->table->next;
	}
	structure->table = head;
	w_id = wait_child_processes(structure, &status);
	free_pipe_structure(structure);
}
