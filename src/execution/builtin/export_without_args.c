/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:47:13 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: export_without_args
 * ------------------------------
 * Handles the 'export' command when no arguments are provided.
 * 
 * structure: A pointer to the main structure containing environment variables and other data.
 * 
 * This function is responsible for displaying all environment variables in a sorted manner
 * when the 'export' command is issued without any arguments. It performs the following steps:
 * 1. Allocates memory and sorts the environment variables.
 * 2. Iterates through the sorted environment variables.
 * 3. For each variable, it counts the number of '=' signs to determine if it has a value.
 * 4. If a variable has a value, it checks whether the value is non-empty and prints accordingly.
 * 5. If a variable does not have an '=' sign, it prints the variable name with "declare -x" prefix.
 * 6. Sets the last exit status to 0 to indicate success.
 * 7. Frees the allocated memory for the sorted environment variables.
 */
void	export_without_args(t_info *structure)
{
	int	i;

	allocate_mem_sort_var(structure); // Step 1: Allocate memory and sort variables
	selectiton_sort_variables(structure->envp_sorted); // Sorts the environment variables
	i = 0;
	while (structure->envp_sorted[i])
	{
		count_number_equal_signs(i, structure->envp_sorted, structure); // Step 3: Count '=' signs
		if (structure->count_number_signs > 0)
		{
			check_has_env_value(i, structure->envp_sorted, structure); // Check if variable has a non-empty value
			if (structure->has_value_envp)
				print_with_env_value(i, structure->envp_sorted, structure); // Step 4: Print variable with value
			else
				print_export_without_value(i, structure->envp_sorted); // Print variable without value if empty
		}
		else
			print_without_equal_sign(i, structure->envp_sorted, "declare -x "); // Step 5: Print variable names without '='
		i++;
	}
	structure->last_exit_status = 0; // Step 6: Set last exit status to 0
	free_2d_array(structure->envp_sorted); // Step 7: Free allocated memory
}