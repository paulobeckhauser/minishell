/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:16:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/09 20:46:08 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

pid_t	wait_child_processes(t_info *structure, int *status)
{
	int	i;
	pid_t w_id;
	// int status;

	i = 0;
	while (i < structure->number_commands)
	{
		w_id = waitpid(structure->pid[i], status, 0);
		i++;
	}
	return(w_id);
}
