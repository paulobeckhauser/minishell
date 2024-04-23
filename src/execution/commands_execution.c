/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:34:03 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/23 18:33:53 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	input_redirections(t_info *structure, int i)
{
	if (structure->table->in.fd == 0)
		handle_no_redirection(structure, i);
	else if (structure->table->in.fd > 0)
		handle_redirection(structure, i);
}

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
