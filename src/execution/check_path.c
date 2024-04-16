/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:43:41 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/16 19:35:25 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_path(char *path, char *cmd)
{
	struct stat	path_stat;

	if (cmd[0] == '.' && cmd[1] == '/')
		path = cmd;
	if (stat(path, &path_stat) == -1 && ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	else if (ft_strncmp(cmd, "./", 2) != 0 && cmd[0] != '/')
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	else if (S_ISREG(path_stat.st_mode))
	{
		if (access(path, X_OK) == -1)
		{
			perror("minishell: ");
			exit(126);
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a file\n", 2);
		exit(errno);
	}
}
