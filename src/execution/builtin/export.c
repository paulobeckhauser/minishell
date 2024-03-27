/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/27 15:26:24 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

static void	export_without_args(t_info *structure)
{
	int		i;
	char	**array;

	selectiton_sort_variables(structure->envp);
	i = 0;
	while (structure->envp[i])
	{
		array = ft_split(structure->envp[i], '=');
		if (array[1])
			printf("declare -x %s=\"%s\"\n", array[0], array[1]);
		else
			printf("declare -x %s\n", structure->envp[i]);
		free_2d_array(array);
		i++;
	}
}

static void	export_with_args(t_info *structure)
{
	int		i;
	int		j;
	int		check;

	check = 0;
	j = 0;
	while (structure->table->arr[1][j])
	{
		if (structure->table->arr[1][j] == '=')
		{
			check++;
			break ;
		}
		j++;
	}
	if (check == 1)
		replace_value_envp(structure);
	else
	{
		if (check_env_variable(structure))
			return ;
		else
			add_to_envp(structure, structure->table->arr[1]);
	}
}

void	execute_export_command(t_info *structure)
{
	if (structure->table->arr[1] == NULL)
		export_without_args(structure);
	else
		export_with_args(structure);
}
