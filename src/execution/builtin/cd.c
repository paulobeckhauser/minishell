/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:16:30 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:40:13 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: is_cd_command
 * -----------------------
 * Checks if the given command is the 'cd' command.
 * 
 * command: The array of strings representing the command and its arguments.
 * 
 * Returns 1 if the first string in the command array is "cd", otherwise returns 0.
 */
int	is_cd_command(char **command)
{
	return (ft_strcmp(command[0], "cd") == 0);
}

/* Function: update_path
 * ---------------------
 * Updates the current working directory in the environment variables.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * This function retrieves the current working directory using getcwd and updates
 * the "PWD" environment variable to reflect the new directory. It handles errors
 * if getcwd fails and frees allocated memory appropriately.
 */
static void	update_path(t_info *structure)
{
	size_t	size;
	char	*cur_path;
	char	*new_string;

	size = PATH_MAX;
	cur_path = getcwd(NULL, size);
	if (cur_path == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	new_string = ft_strjoin("PWD=", cur_path);
	free(cur_path);
	structure->envp = delete_string_array(structure->envp, "PWD");
	structure->envp_export = delete_string_array(structure->envp_export, "PWD");
	add_to_envp(structure, new_string, 1);
	free(new_string);
}

/* Function: execute_handle_error_cd
 * ---------------------------------
 * Changes the current working directory and handles errors.
 * 
 * path: The path to change the current working directory to.
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * This function attempts to change the current working directory to the specified path.
 * If the operation fails, it prints an error message and sets the last exit status to failure.
 * It also updates the "PWD" environment variable to reflect the new directory.
 */
void	execute_handle_error_cd(char *path, t_info *structure)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(structure->table->arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
	}
	update_path(structure);
}

/* Function: execute_cd_command
 * ----------------------------
 * Executes the 'cd' command.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * This function determines the number of arguments provided to the 'cd' command and
 * executes the command accordingly. It supports changing to the "HOME" directory with
 * no arguments, changing to a specified directory with one argument, and prints an error
 * message if too many arguments are provided.
 */
void	execute_cd_command(t_info *structure)
{
	char	*path;
	int		nb_args;

	nb_args = 0;
	while (structure->table->arr[nb_args])
		nb_args++;
	if (nb_args == 1)
		cd_wihtout_args(structure);
	else if (nb_args == 2)
	{
		path = structure->table->arr[1];
		execute_handle_error_cd(path, structure);
	}
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
	}
}