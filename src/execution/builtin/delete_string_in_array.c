/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_string_in_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:36:38 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 10:39:32 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	**allocate_mem_backup_array(t_info *structure, char *str_delete)
{
	int		i;
	int		j;
	char	**env_var;
	char	**array_backup;

	i = 0;
	j = 0;
	while (structure->envp[i])
	{
		env_var = ft_split(structure->envp[i], '=');
		if (ft_strcmp(str_delete, env_var[0]) == 0)
			j++;
		i++;
		free_2d_array(env_var);
	}
	array_backup = (char **)malloc((i - j + 1) * sizeof(char *));
	return (array_backup);
}

static char	**copy_backup_array(t_info *structure, char *str_delete)
{
	int		i;
	int		j;
	char	**env_var;
	char	**array_backup;

	i = 0;
	j = 0;
	while (structure->envp[i])
	{
		env_var = ft_split(structure->envp[i], '=');
		if (ft_strcmp(str_delete, env_var[0]) != 0)
		{
			array_backup[j] = ft_strdup(structure->envp[i]);
			j++;
		}
		i++;
	}
	array_backup[j] = NULL;
	return (array_backup);
}

void	delete_string_in_array(t_info *structure, char *str_delete)
{
	int		i;
	int		j;
	char	**array_backup;
	char	**env_var;

	array_backup = allocate_mem_backup_array(structure, str_delete);
	array_backup = copy_backup_array(structure, str_delete);
	free_2d_array(structure->envp);
	i = 0;
	while (array_backup[i])
		i++;
	structure->envp = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (array_backup[i])
	{
		structure->envp[i] = ft_strdup(array_backup[i]);
		i++;
	}
	structure->envp[i] = NULL;
}
