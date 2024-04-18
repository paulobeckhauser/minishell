/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:43:41 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 16:19:13 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	no_file_directory(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

static void	comm_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

static void	is_directory(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	exit(126);
}

static void	is_file(char *path)
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

void	check_path(char *path, char *cmd)
{
	struct stat	path_stat;

	if (cmd[0] == '.' && cmd[1] == '/')
		path = cmd;
	if (stat(path, &path_stat) == -1 && ((cmd[0] == '.' && cmd[1] == '/')
			|| cmd[0] == '/'))
		no_file_directory(cmd);
	else if (ft_strncmp(cmd, "./", 2) != 0 && cmd[0] != '/')
		comm_not_found(cmd);
	else if (S_ISDIR(path_stat.st_mode))
		is_directory(path);
	else if (S_ISREG(path_stat.st_mode))
		is_file(path);
}
