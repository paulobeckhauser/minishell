/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:48:57 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/09 18:50:04 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void commands_error_handling(t_info *structure)
{
	int i;
	
	i = 0;
	while (structure->path_commands[i])
	{
		if (access(structure->path_commands[i], X_OK) == 0)
		{
			structure->last_exit_status = EX_SUCESS;
		}
		else
		{
			ft_putstr_fd(structure->commands[i], 2);
			ft_putstr_fd(": command not found\n", 2);
			structure->last_exit_status = EX_COMM_NOTFOUND;
			
		}
		i++;
	}

}