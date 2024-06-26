/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:28 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/23 12:34:50 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_env_command(char **command)
{
	return (ft_strcmp(command[0], "env") == 0);
}

void	execute_env_command(t_info *structure)
{
	int	i;

	i = 0;
	while (structure->envp[i])
	{
		ft_putstr_fd(structure->envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free(structure->path_env);
}
