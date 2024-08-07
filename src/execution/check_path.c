/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:43:41 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 16:19:13 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: no_file_directory
 * ---------------------------
 * Prints an error message for when a file or directory cannot be found.
 * 
 * cmd: The command that was attempted to be executed.
 * 
 * This function prints an error message to standard error indicating that the
 * specified file or directory does not exist, then exits with status code 127.
 */
static void	no_file_directory(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

/* Function: comm_not_found
 * ------------------------
 * Prints an error message for when a command cannot be found.
 * 
 * cmd: The command that was attempted to be executed.
 * 
 * This function prints an error message to standard error indicating that the
 * specified command was not found, then exits with status code 127.
 */
static void	comm_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

/* Function: is_directory
 * ----------------------
 * Prints an error message for when the specified path is a directory.
 * 
 * path: The path that was attempted to be executed.
 * 
 * This function prints an error message to standard error indicating that the
 * specified path is a directory, then exits with status code 126.
 */
static void	is_directory(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	exit(126);
}

/* Function: is_file
 * -----------------
 * Checks if the specified path is an executable file.
 * 
 * path: The path that was attempted to be executed.
 * 
 * This function checks if the specified path is an executable file. If it is not
 * executable, it prints an error message using perror and exits with status code 126.
 * If it is an executable file, it prints a message indicating so, then exits with the
 * current errno value.
 */
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

/* Function: check_path
 * --------------------
 * Checks the path of a command and determines its validity.
 * 
 * path: The path to the command.
 * cmd: The command that was attempted to be executed.
 * 
 * This function checks the path of a command to determine if it is valid. It handles
 * different cases such as when the command is a relative path (starts with "./"), an
 * absolute path (starts with "/"), or neither. It then calls the appropriate function
 * based on whether the path is a directory, a file, or does not exist.
 */
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