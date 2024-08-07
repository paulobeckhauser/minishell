/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_without_value.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:33:18 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:48:49 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: print_export_without_value
 * -------------------------------------
 * Prints an environment variable name prefixed with "declare -x" and followed by empty quotes.
 * 
 * i: The index of the current environment variable in the sorted array.
 * envp_sorted: A sorted array of environment variables.
 * 
 * This function first prints the "declare -x " prefix. Then, it iterates over the characters
 * of the environment variable at the given index, printing each character. After printing the
 * entire variable name, it prints two double quotes to indicate an empty value and ends with a newline.
 */
void	print_export_without_value(int i, char **envp_sorted)
{
	int	j;

	j = 0;
	print_export_structure("declare -x ");
	while (envp_sorted[i][j])
	{
		ft_putchar_fd(envp_sorted[i][j], 1);
		j++;
	}
	ft_putchar_fd('\"', 1);
	ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}