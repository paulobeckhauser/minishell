/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:16:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/04 15:20:01 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_child_processes(t_info *structure)
{
	int	i;

	i = 0;
	while (i < structure->number_commands)
	{
		waitpid(structure->pid[i], NULL, 0);
		i++;
	}
}
