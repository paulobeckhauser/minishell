/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_with_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:33:28 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/21 16:43:59 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: print_export_with_value
 * ----------------------------------
 * Prints an environment variable and its value with quotes around the value.
 * 
 * i: The index of the current environment variable in the sorted array.
 * envp_sorted: A sorted array of environment variables.
 * number_equal_sign: The index of the '=' character in the environment variable string.
 * 
 * This function iterates over each character of the environment variable at the given index.
 * If it encounters the '=' character at the expected position (number_equal_sign), it prints
 * a double quote before proceeding. It then prints the character and, if it's the last character
 * in the string and there was an '=' character, it prints a closing double quote before a newline.
 */
void	print_export_with_value(int i, char **envp_sorted,
		int number_equal_sign)
{
	int	j;

	j = 0;
	while (envp_sorted[i][j])
	{
		if (j > 0 && envp_sorted[i][j - 1] == '=' && number_equal_sign == j - 1)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd(envp_sorted[i][j], 1);
		if (envp_sorted[i][j + 1] == '\0' && number_equal_sign > 0)
			ft_putchar_fd('\"', 1);
		j++;
	}
	ft_putchar_fd('\n', 1);
}

/* Function: print_with_env_value
 * -------------------------------
 * Prepares and prints an environment variable with its value, including quotes around the value.
 * 
 * i: The index of the current environment variable in the sorted array.
 * envp_sorted: A sorted array of environment variables.
 * structure: A pointer to the main structure containing environment variables and other data.
 * 
 * This function first finds the index of the '=' character in the environment variable string.
 * It then prints the "declare -x " prefix before calling print_export_with_value to print the
 * environment variable name, its value with quotes, and a newline.
 */
void	print_with_env_value(int i, char **envp_sorted, t_info *structure)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (envp_sorted[i][j])
	{
		k = 0;
		while (envp_sorted[i][k] != '=')
			k++;
		if (envp_sorted[i][k] == '=')
			structure->number_equal_sign = k;
		j++;
	}
	print_export_structure("declare -x ");
	print_export_with_value(i, envp_sorted, structure->number_equal_sign);
}