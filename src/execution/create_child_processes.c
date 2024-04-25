/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child_processes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:03:28 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 12:05:06 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_child_processes(t_info *structure)
{
	int	i;

	structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1),
			sizeof(pid_t));
	if (!structure->pid)
		mem_alloc_protection();
	i = 0;
	while (i < structure->number_commands)
	{
		structure->pid[i] = fork();
		if (structure->pid[i] == 0)
		{
			if (i != 0)
			{
				dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
				close(structure->fds_pipes[i - 1][0]);
			}
			if (i != structure->number_commands - 1)
			{
				dup2(structure->fds_pipes[i][1], 1);
				close(structure->fds_pipes[i][1]);
			}
			execve(structure->path_commands[i], structure->table->arr,
				structure->envp);
		}
		i++;
	}
}
