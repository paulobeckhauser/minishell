/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_has_env_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:11:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:18:58 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: check_has_env_value
 * -----------------------------
 * Checks if an environment variable has a value.
 * 
 * i: The index of the environment variable in the sorted environment variables array.
 * envp_sorted: The sorted array of environment variables.
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * This function iterates through the characters of the environment variable at index i
 * until it finds the '=' character, which separates the variable name from its value.
 * If there is a character immediately following '=', it sets structure->has_value_envp to 1,
 * indicating that the environment variable has a value. Otherwise, it sets it to 0,
 * indicating that the variable does not have a value.
 */
void	check_has_env_value(int i, char **envp_sorted, t_info *structure)
{
	int	j;

	j = 0;
	while (envp_sorted[i][j] && envp_sorted[i][j] != '=')
		j++;
	if (envp_sorted[i][j + 1])
		structure->has_value_envp = 1;
	else
		structure->has_value_envp = 0;
}