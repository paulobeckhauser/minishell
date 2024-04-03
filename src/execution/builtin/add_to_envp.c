/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:38:08 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:19:39 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	**add_variable_to_array(char *str_add, char **array)
{
	char	**backup_array;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (array[i])
		i++;
	backup_array = (char **)malloc((i + 1) * sizeof(char *));
	j = 0;
	while (array[j])
	{
		backup_array[j] = ft_strdup(array[j]);
		j++;
	}
	free_2d_array(array);
	array = (char **)malloc((i + 2) * sizeof(char *));
	k = 0;
	while (backup_array[k])
	{
		array[k] = ft_strdup(backup_array[k]);
		k++;
	}
	array[k] = ft_strdup(str_add);
	k++;
	array[k] = NULL;
	free_2d_array(backup_array);
	return (array);
}

void	add_to_envp(t_info *structure, char *str_add, int check_equal_sign)
{
	if (check_equal_sign == 1)
		structure->envp = add_variable_to_array(str_add, structure->envp);
	structure->envp_export = add_variable_to_array(str_add,
			structure->envp_export);
}
