/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:16:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 20:22:41 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

pid_t	wait_child_processes(t_info *structure, int *status)
{
	int		i;
	pid_t	w_id;
	int		exit_status;

	i = 0;
	while (i < structure->number_commands)
	{
		w_id = waitpid(structure->pid[i], status, 0);
		if (WIFEXITED(*status))
		{
			exit_status = WEXITSTATUS(*status);
			structure->last_exit_status = exit_status;
		}
		i++;
	}
	return (w_id);
}
