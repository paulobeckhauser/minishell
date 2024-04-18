/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:43:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 14:50:40 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	export_without_args(t_info *structure)
{
	int	i;

	allocate_mem_sort_var(structure);
	selectiton_sort_variables(structure->envp_sorted);
	i = 0;
	while (structure->envp_sorted[i])
	{
		count_number_equal_signs(i, structure->envp_sorted, structure);
		if (structure->count_number_signs > 0)
		{
			check_has_env_value(i, structure->envp_sorted, structure);
			if (structure->has_value_envp)
				print_with_env_value(i, structure->envp_sorted, structure);
			else
				print_export_without_value(i, structure->envp_sorted);
		}
		else
			print_without_equal_sign(i, structure->envp_sorted, "declare -x ");
		i++;
	}
	structure->last_exit_status = 0;
	free_2d_array(structure->envp_sorted);
}
