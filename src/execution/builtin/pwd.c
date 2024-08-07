/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:36:05 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/16 12:23:42 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: is_pwd_command
 * ------------------------
 * Checks if the given command is the 'pwd' command.
 * 
 * command: A pointer to an array of strings representing the command and its arguments.
 * 
 * Returns 1 (true) if the first string in the command array is "pwd", otherwise returns 0 (false).
 */
int	is_pwd_command(char **command)
{
	return (ft_strcmp(command[0], "pwd") == 0);
}

/* Function: execute_pwd_command
 * ------------------------------
 * Executes the 'pwd' command, printing the current working directory.
 * 
 * command: A pointer to an array of strings representing the command and its arguments.
 *          This parameter is unused in the function and is marked as such to avoid compiler warnings.
 * 
 * The function first attempts to retrieve the current working directory using getcwd, allocating
 * enough space for the path. If getcwd returns NULL, indicating an error, it prints an error message.
 * Otherwise, it prints the current working directory followed by a newline, then frees the allocated memory.
 */
void	execute_pwd_command(char **command)
{
	char	*cur_path;
	size_t	size;

	(void)command; // Mark command as unused
	size = PATH_MAX;
	cur_path = getcwd(NULL, size);
	if (cur_path == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	printf("%s\n", cur_path);
	free(cur_path);
}