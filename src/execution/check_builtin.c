/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:09:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/04 15:09:41 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: check_builtin
 * -----------------------
 * Checks if the given string matches any of the shell's builtin commands.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * str: The command string to check.
 * 
 * This function compares the given string with the names of all builtin commands
 * (echo, cd, pwd, export, unset, env, exit). If a match is found, it sets the is_builtin
 * flag in the structure to 1, indicating that the command is a builtin command. Otherwise,
 * it sets the flag to 0.
 */
void	check_builtin(t_info *structure, char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		structure->is_builtin = 1;
	else
		structure->is_builtin = 0;
}