/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:03 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 12:54:34 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	edge_cases_handle(t_info *structure, int k)
{
	int	i;

	i = 0;
	if (((structure->table->arr[k][i] == '-') && (structure->table->arr[k][i
				+ 1] != '-')) || (structure->table->arr[k][i + 1] == '-')
		|| (structure->table->arr[k][i] >= '0'
			&& structure->table->arr[k][i] <= '9'))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(structure->table->arr[k], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
	}
}

static void	iter_and_check(t_info *structure, int k)
{
	int	i;

	i = 0;
	ft_putstr_fd("bash: export: `", 2);
	// m = 0;
	while (structure->table->arr[k][i])
	{
		ft_putchar_fd(structure->table->arr[k][i], 2);
		i++;
	}
	ft_putstr_fd("': not a valid identifier\n", 2);
	structure->last_exit_status = 1;
}

void	export_with_args(t_info *structure)
{
	int	i;
	int	check_equal_sign;
	int	k;

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
			edge_cases_handle(structure, k);
			check_equal_sign = 0;
			i = 0;
			while (structure->table->arr[k][i])
			{
				if (structure->table->arr[k][i] == '=')
				{
					if (structure->table->arr[k][i - 1]
						&& structure->table->arr[k][i - 1] == '-')
					{
						iter_and_check(structure, k);
						break ;
					}
					check_equal_sign++;
					break ;
				}
				i++;
			}
			if (check_equal_sign == 1)
				replace_value_envp(structure, check_equal_sign);
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
