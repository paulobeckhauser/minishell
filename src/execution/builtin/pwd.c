/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:36:05 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 22:25:32 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_pwd_command(char **command)
{
	return (ft_strcmp(command[0], "pwd") == 0);
}

void	execute_pwd_command(char **command)
{
	char	*cur_path;

	(void)command;
	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	printf("%s\n", cur_path);
	free(cur_path);
}
