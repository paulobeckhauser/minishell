/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:38:08 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 10:53:03 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	replace_array_values(t_info *structure, char **backup_array,
		char *str_add)
{
	int	i;

	i = 0;
	while (backup_array[i])
	{
		structure->envp[i] = ft_strdup(backup_array[i]);
		i++;
	}
	structure->envp[i] = ft_strdup(str_add);
	i++;
	structure->envp[i] = NULL;
}

void	add_to_envp(t_info *structure, char *str_add)
{
	char	**backup_array;
	int		i;
	int		j;

	i = 0;
	while (structure->envp[i])
		i++;
	backup_array = (char **)malloc((i + 1) * sizeof(char *));
	j = 0;
	while (structure->envp[j])
	{
		backup_array[j] = ft_strdup(structure->envp[j]);
		j++;
	}
	free_2d_array(structure->envp);
	structure->envp = (char **)malloc((i + 2) * sizeof(char *));
	replace_array_values(structure, backup_array, str_add);
	free_2d_array(backup_array);
}
