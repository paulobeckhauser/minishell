/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:50:31 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 10:37:19 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	get_lenght(char **envp)
{
	int	length;

	length = 0;
	while (envp[length])
		length++;
	return (length);
}

static int	str_compare(int j, int length, int j_min, char **envp)
{
	while (j < length)
	{
		if (ft_strcmp(envp[j], envp[j_min]) < 0)
			j_min = j;
		j++;
	}
	return (j_min);
}

void	selectiton_sort_variables(char **envp)
{
	int		length;
	int		i;
	int		j;
	int		j_min;
	char	*temp;

	length = get_lenght(envp);
	i = 0;
	while (i < length - 1)
	{
		j_min = i;
		j = i + 1;
		j_min = str_compare(j, length, j_min, envp);
		if (j_min != i)
		{
			temp = envp[i];
			envp[i] = envp[j_min];
			envp[j_min] = temp;
		}
		i++;
	}
}

void	replace_value_envp(t_info *structure)
{
	char	**array;

	array = ft_split(structure->table->arr[1], '=');
	delete_string_in_array(structure, array[0]);
	add_to_envp(structure, structure->table->arr[1]);
	free_2d_array(array);
}
