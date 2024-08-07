/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:27:59 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:41:24 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: flag_string_only_n
 * -----------------------------
 * Checks if a string consists only of '-n' flags.
 * 
 * str: The string to check.
 * 
 * Returns 1 if the string is composed only of '-n' flags, otherwise returns 0.
 * The function counts the number of 'n' characters after a '-' and compares it
 * to the total length of the string to determine if it matches the '-n' pattern.
 */
int	flag_string_only_n(char *str)
{
	int	size_str;
	int	count_n;
	int	i;

	size_str = ft_strlen(str);
	i = 0;
	count_n = 0;
	if (str[i] == '-')
	{
		i++;
		count_n++;
		while (str[i])
		{
			if (str[i] == 'n')
				count_n++;
			i++;
		}
	}
	if (size_str == count_n)
		return (1);
	return (0);
}

/* Function: echo_n_flag
 * ---------------------
 * Processes the '-n' flag for the echo command and constructs the output string.
 * 
 * string: The initial string to be processed.
 * structure: A pointer to the main structure containing the command arguments.
 * i: The index to start processing from within the command arguments.
 * 
 * Frees the initial string and checks if there are more arguments after the '-n' flag.
 * It skips all consecutive '-n' flags and then joins the remaining arguments into a single
 * string to be echoed. If there are no arguments after the '-n' flags, it returns an empty string.
 * 
 * Returns the final string to be echoed.
 */
char	*echo_n_flag(char *string, t_info *structure, int i)
{
	free(string);
	if (structure->table->arr[2])
	{
		while (structure->table->arr[i])
		{
			if (ft_strcmp(structure->table->arr[i], "-n") == 0)
				i++;
			else
				break ;
		}
		if (structure->table->arr[i])
			string = join_string_echo(i, structure);
		else
			string = ft_strdup("");
	}
	else
		string = ft_strdup("");
	return (string);
}