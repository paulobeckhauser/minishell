/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_number_equal_signs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:40:44 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:40:57 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: count_number_equal_signs
 * -----------------------------------
 * Counts the number of '=' characters in an environment variable string.
 * 
 * i: The index of the environment variable in the sorted environment variables array.
 * envp_sorted: The sorted array of environment variables.
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * This function iterates through the characters of the environment variable at index i,
 * counting the number of '=' characters. The count is stored in structure->count_number_signs.
 */
void	count_number_equal_signs(int i, char **envp_sorted, t_info *structure)
{
	int	j;

	j = 0;
	structure->count_number_signs = 0;
	while (envp_sorted[i][j])
	{
		if (envp_sorted[i][j] == '=')
			structure->count_number_signs++;
		j++;
	}
}

/* Function: count_equal_sign
 * ---------------------------
 * Counts the number of '=' characters in the first argument of the command.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * This function iterates through the characters of the first argument of the command,
 * counting the number of '=' characters. The count is stored in structure->count_equal_sign.
 */
void	count_equal_sign(t_info *structure)
{
	int	i;

	i = 0;
	structure->count_equal_sign = 0;
	while (structure->table->arr[1][i])
	{
		if (structure->table->arr[1][i] == '=')
			structure->count_equal_sign++;
		i++;
	}
}