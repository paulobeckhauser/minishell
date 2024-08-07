/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_without_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:08:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:42:16 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: echo_without_flag
 * ----------------------------
 * Handles the echo command when no flags are provided.
 * 
 * string: The initial string to be processed.
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * This function constructs the string to be echoed when the echo command is called
 * without any flags. It joins all command arguments starting from the first argument
 * with spaces, appends a newline character at the end, and returns the resulting string.
 * 
 * Returns the final string to be echoed.
 */
char	*echo_without_flag(char *string, t_info *structure)
{
	char	*first_backup_string;
	char	*second_backup_string;

	first_backup_string = join_string_echo(1, structure);
	second_backup_string = ft_strjoin(first_backup_string, "\n");
	free(string);
	string = ft_strdup(second_backup_string);
	free(first_backup_string);
	free(second_backup_string);
	return (string);
}