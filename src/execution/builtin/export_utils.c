/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:50:31 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:00:40 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	replace_value_envp(t_info *structure, int check_equal_sign)
{
	char	**array;
	int		count_equal_sign;
	int		i;
	int		first_equal_sign;
	int		j;
	int k;
	char *new_string;

	i = 0;
	count_equal_sign = 0;
	while (structure->table->arr[1][i])
	{
		if (structure->table->arr[1][i] == '=')
			count_equal_sign++;
		i++;
	}
	first_equal_sign = 0;
	j = 0;
	if (count_equal_sign > 1)
	{
		while (structure->table->arr[1][j]
			&& structure->table->arr[1][j] != '=')
		{
			j++;
		}
		if (structure->table->arr[1][j] == '=')
			first_equal_sign = j;
		j = 0;
		while (structure->table->arr[1][j])
		{
			if (j != first_equal_sign && structure->table->arr[1][j] == '=')
			{
				structure->table->arr[1][j] = 2;
			}
			j++;
		}
	}
	array = ft_split(structure->table->arr[1], '=');
	if (array[1])
	{
		k = 0;
		while (array[1][k])
		{
			if (array[1][k] == 2)
				array[1][k] = '=';
			k++;
		}
		new_string = ft_strjoin(array[0], "=");
		new_string = ft_strjoin(new_string, array[1]);
		structure->envp = delete_string_array(structure->envp, array[0]);
		structure->envp_export = delete_string_array(structure->envp_export,
				array[0]);
		add_to_envp(structure, new_string, check_equal_sign);
		free_2d_array(array);
	}
	else
	{
		new_string = ft_strjoin(array[0], "=");
		structure->envp = delete_string_array(structure->envp, array[0]);
		structure->envp_export = delete_string_array(structure->envp_export,
				array[0]);
		add_to_envp(structure, new_string, check_equal_sign);
		free_2d_array(array);
	}
}
