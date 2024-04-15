/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:16:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/15 11:49:55 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// pid_t	wait_child_processes(t_info *structure, int *status)
// {
// 	int	i;
// 	pid_t w_id;
// 	// int status;

// 	i = 0;
// 	while (i < structure->number_commands)
// 	{
// 		w_id = waitpid(structure->pid[i], status, 0);
// 		i++;
// 	}
// 	return(w_id);
// }

pid_t	wait_child_processes(t_info *structure, int *status)
{
    int	i;
    pid_t w_id;
    int exit_status;

    i = 0;
    while (i < structure->number_commands)
    {
        w_id = waitpid(structure->pid[i], status, 0);
        if (WIFEXITED(*status))
        {
            exit_status = WEXITSTATUS(*status);
            structure->last_exit_status = exit_status;
			// if (structure->last_exit_status == 127)
			// {
			// 	ft_putstr_fd("minishell: command not found\n", 2);
			// 	perror("command not found\n");
			// }
			// if (structure->last_exit_status != 0)
			// {
			// 	ft_putstr_fd("minishell: ", 2);
			// 	perror(NULL);
			// }
        }
        i++;
    }
    return(w_id);
}
