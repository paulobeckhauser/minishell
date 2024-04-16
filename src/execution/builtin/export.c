/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/16 12:24:43 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

static void	export_without_args(t_info *structure)
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
	free_2d_array(structure->envp_sorted);
}

static void	export_with_args(t_info *structure)
{
	int	i;
	int	check_equal_sign;
	int	k;
						int m;

	k = 1;
	while (structure->table->arr[k])
	{
		if (ft_strcmp(structure->table->arr[k], "=") == 0)
		{
			ft_putstr_fd("bash: export: `=': not a valid identifier\n", 2);
			structure->last_exit_status = 1;
		}
		else
		{
			i = 0;
			if (((structure->table->arr[k][i] == '-')
					&& (structure->table->arr[k][i + 1] != '-'))
				|| (structure->table->arr[k][i + 1] == '-')
				|| (structure->table->arr[k][i] >= '0'
					&& structure->table->arr[k][i] <= '9'))
			{
				ft_putstr_fd("bash: export: `", 2);
				ft_putstr_fd(structure->table->arr[k], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				structure->last_exit_status = EXIT_FAILURE;
			}
			check_equal_sign = 0;
			i = 0;
			while (structure->table->arr[k][i])
			{
				if (structure->table->arr[k][i] == '=')
				{
					if (structure->table->arr[k][i - 1]
						&& structure->table->arr[k][i - 1] == '-')
					{
						ft_putstr_fd("bash: export: `", 2);
						m = 0;
						while (structure->table->arr[k][m])
						{
							ft_putchar_fd(structure->table->arr[k][m], 2);
							m++;
						}
						ft_putstr_fd("': not a valid identifier\n", 2);
						structure->last_exit_status = 1;
						break ;
					}
					check_equal_sign++;
					break ;
				}
				i++;
			}
			if (check_equal_sign == 1)
			{
				replace_value_envp(structure, check_equal_sign);
			}
			else
			{
				if (check_env_variable(structure))
					return ;
				else
					add_to_envp(structure, structure->table->arr[k],
						check_equal_sign);
			}
		}
		k++;
	}
}

void	execute_export_command(t_info *structure)
{
	if (structure->table->arr[1] == NULL)
		export_without_args(structure);
	else
		export_with_args(structure);
}
