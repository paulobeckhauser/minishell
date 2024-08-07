/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/21 18:29:21 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: is_echo_command
 * -------------------------
 * Checks if the first command argument is "echo".
 * 
 * command: The array of command arguments.
 * 
 * Returns 1 if the first command argument is "echo", otherwise returns 0.
 * This function is used to determine if the command being processed is an echo command.
 */
int	is_echo_command(char **command)
{
	return (ft_strcmp(command[0], "echo") == 0);
}

/* Function: redirection_echo
 * ---------------------------
 * Redirects the echo output to the specified file descriptor or standard output.
 * 
 * string: The string to be echoed.
 * structure: A pointer to the main structure containing redirection information.
 * 
 * If a file descriptor for output redirection is specified in the structure, the function
 * writes the string to that file descriptor. Otherwise, it writes to the standard output.
 * After writing, if a file descriptor was used, it attempts to close it and handles errors.
 */
static void	redirection_echo(char *string, t_info *structure)
{
	if (structure->table->out.file_name)
	{
		ft_putstr_fd(string, structure->table->out.fd);
		if (close(structure->table->out.fd) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror("close");
			return ;
		}
	}
	else
		ft_putstr_fd(string, STDOUT_FILENO);
}

/* Function: condition_flag
 * ------------------------
 * Determines the string to echo based on the presence of the '-n' flag.
 * 
 * n_flag: Indicates whether the '-n' flag is present (1) or not (0).
 * string: The initial string to be processed.
 * structure: A pointer to the main structure containing the command arguments.
 * i: The index to start processing from within the command arguments.
 * 
 * If the '-n' flag is present, it processes the command arguments accordingly,
 * otherwise, it processes them as if no flag was provided.
 * 
 * Returns the final string to be echoed.
 */
static char	*condition_flag(int n_flag, char *string, t_info *structure, int i)
{
	if (n_flag)
		string = echo_n_flag(string, structure, i);
	else
		string = echo_without_flag(string, structure);
	return (string);
}

/* Function: execute_echo_command
 * -------------------------------
 * Executes the echo command with or without the '-n' flag.
 * 
 * structure: A pointer to the main structure containing the command arguments and redirection information.
 * 
 * This function processes the echo command, handling the '-n' flag and output redirection.
 * It constructs the string to be echoed based on the command arguments and the presence of the '-n' flag,
 * then redirects the output to the appropriate file descriptor or standard output, and finally frees the
 * constructed string.
 */
void	execute_echo_command(t_info *structure)
{
	char	*string;
	int		n_flag;
	int		i;

	n_flag = 0;
	string = NULL;
	i = 1;
	if (structure->table->arr[1])
	{
		while (structure->table->arr[i])
		{
			if (flag_string_only_n(structure->table->arr[i]))
			{
				n_flag = 1;
				i++;
			}
			else
				break ;
		}
		string = condition_flag(n_flag, string, structure, i);
	}
	else
		string = ft_strdup("\n");
	redirection_echo(string, structure);
	free(string);
}