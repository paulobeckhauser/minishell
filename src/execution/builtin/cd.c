/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:16:30 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/13 14:06:36 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_cd_command(char **command)
{
	return (ft_strcmp(command[0], "cd") == 0);
}

void	execute_cd_command(char **command)
{
	char	*path;

	if (command[1] == NULL)
		path = getenv("HOME");
	else
		path = command[1];
	if (chdir(path) == -1)
		perror("cd failed");
}
