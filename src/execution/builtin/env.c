/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:28 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:44:07 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: is_env_command
 * ------------------------
 * Checks if the first command argument is "env".
 * 
 * command: The array of command arguments.
 * 
 * Returns 1 if the first command argument is "env", otherwise returns 0.
 * This function is used to determine if the command being processed is an env command.
 */
int	is_env_command(char **command)
{
	return (ft_strcmp(command[0], "env") == 0);
}

/* Function: execute_env_command
 * ------------------------------
 * Executes the env command by printing all environment variables.
 * 
 * structure: A pointer to the main structure containing environment variables.
 * 
 * Iterates through the environment variables stored in structure->envp and prints
 * each one followed by a newline. After printing all environment variables, it frees
 * the memory allocated for the path environment variable stored in structure->path_env.
 */
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