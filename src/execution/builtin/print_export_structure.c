/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_structure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:19:10 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: print_export_structure
 * ---------------------------------
 * Prints a given string character by character to the standard output.
 * 
 * str_declare: The string to be printed.
 * 
 * This function iterates over each character in the string and prints it
 * using the ft_putchar_fd function, which writes a character to a given file descriptor.
 * In this case, the file descriptor is 1, which corresponds to the standard output.
 */
void	print_export_structure(char *str_declare)
{
	int	i;

	i = 0;
	while (str_declare[i])
	{
		ft_putchar_fd(str_declare[i], 1);
		i++;
	}
}

/* Function: print_without_equal_sign
 * -----------------------------------
 * Prints the "declare -x" prefix followed by an environment variable name.
 * 
 * i: The index of the current environment variable in the sorted array.
 * envp_sorted: A sorted array of environment variables.
 * string_declare: The prefix to be printed before the environment variable name.
 * 
 * This function first prints the given prefix (e.g., "declare -x ") character by character.
 * Then, it prints the name of the environment variable at the given index in the sorted array.
 * Finally, it prints a newline character to move to the next line.
 */
void	print_without_equal_sign(int i, char **envp_sorted,
		char *string_declare)
{
	int	j;

	j = 0;
	while (string_declare[j])
	{
		ft_putchar_fd(string_declare[j], 1);
		j++;
	}
	j = 0;
	while (envp_sorted[i][j])
	{
		ft_putchar_fd(envp_sorted[i][j], 1);
		j++;
	}
	ft_putchar_fd('\n', 1);
}