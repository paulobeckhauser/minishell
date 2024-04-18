/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:03 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 16:17:26 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	edge_cases_handle(t_info *structure, int i)
{
	int	j;
	int flag_edge_cases;

	flag_edge_cases = 0;
	j = 0;
	if (((structure->table->arr[i][j] == '-') && (
			structure->table->arr[i][j + 1] != '-'))
			|| (structure->table->arr[i][j + 1] == '-')
			|| (structure->table->arr[i][j] >= '0'
			&& structure->table->arr[i][j] <= '9'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(structure->table->arr[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
		flag_edge_cases = 1;
	}
	return (flag_edge_cases);
}

static void	iter_and_check(t_info *structure, int i)
{
	int	j;

	j = 0;
	ft_putstr_fd("minishell: export: `", 2);
	while (structure->table->arr[i][j])
	{
		ft_putchar_fd(structure->table->arr[i][j], 2);
		j++;
	}
	ft_putstr_fd("': not a valid identifier\n", 2);
	structure->last_exit_status = 1;
}

static void	change_envp(int check_equal_sign, t_info *structure, int k)
{
	if (check_equal_sign == 1)
	{
		replace_value_envp(structure, check_equal_sign);
	}
	else
	{
		if (check_env_variable(structure))
		{
			return ;
		}
		else
		{
			add_to_envp(structure, structure->table->arr[k], check_equal_sign);
		}
	}
}

static int	nb_equal_signs(t_info *structure, int i)
{
	int	check_equal_sign;
	int	j;

	j = 0;
	check_equal_sign = 0;
	while (structure->table->arr[i][j])
	{
		if (structure->table->arr[i][j] == '=')
		{
			if (structure->table->arr[i][j - 1] && structure->table->arr[i][j
				- 1] == '-')
			{
				iter_and_check(structure, i);
				break ;
			}
			check_equal_sign++;
			break ;
		}
		j++;
	}
	return (check_equal_sign);
}

void	export_with_args(t_info *structure)
{
	int	check_equal_sign;
	int	i;

	i = 1;
	while (structure->table->arr[i])
	{
		if (ft_strcmp(structure->table->arr[i], "=") == 0)
		{
			ft_putstr_fd("bash: export: `=': not a valid identifier\n", 2);
			structure->last_exit_status = 1;
		}
		else
		{
			if (edge_cases_handle(structure, i) == 0)
			{
				check_equal_sign = 0;
				check_equal_sign = nb_equal_signs(structure, i);
				change_envp(check_equal_sign, structure, i);
				
			}
		}
		i++;
	}
}
