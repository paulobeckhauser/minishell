/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 17:00:21 by pabeckha         ###   ########.fr       */
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
	char 	**envp_sorted;
	int len;
	
	len = 0;
	while (structure->envp_export[len])
		len++;
	envp_sorted = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	while(structure->envp_export[i])
	{
		envp_sorted[i] = ft_strdup(structure->envp_export[i]);
		i++;
	}
	envp_sorted[i] = NULL;
	selectiton_sort_variables(envp_sorted);
	i = 0;
	while (envp_sorted[i])
	{
		array = ft_split(envp_sorted[i], '=');
		if (array[1])
			printf("declare -x %s=\"%s\"\n", array[0], array[1]);
		else
			printf("declare -x %s\n", envp_sorted[i]);
		free_2d_array(array);
		i++;
	}
	free_2d_array(envp_sorted);
}

static void	export_with_args(t_info *structure)
{
	int		i;
	int		j;
	int		check_equal_sign;

	check_equal_sign = 0;
	j = 0;
	while (structure->table->arr[1][j])
	{
		if (structure->table->arr[1][j] == '=')
		{
			check_equal_sign++;
			break ;
		}
		j++;
	}
	if (check_equal_sign == 1)
		replace_value_envp(structure, check_equal_sign);
	else
	{
		if (check_env_variable(structure->envp, structure))
			return ;
		else
			add_to_envp(structure, structure->table->arr[1], check_equal_sign);
	}
}

void	execute_export_command(t_info *structure)
{
	if (structure->table->arr[1] == NULL)
		export_without_args(structure);
	else
		export_with_args(structure);
}
