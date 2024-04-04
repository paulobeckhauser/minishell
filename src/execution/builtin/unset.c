/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:53:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/04 11:49:21 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_unset_command(char **command)
{
	return (ft_strcmp(command[0], "unset") == 0);
}

static char	**allocate_mem_array_backup(char **array, char **array_backup,
		char *str_delete)
{
	int		i;
	int		count;
	char	**env_var;

	i = 0;
	count = 0;
	while (array[i])
	{
		env_var = ft_split(array[i], '=');
		if (ft_strcmp(str_delete, env_var[0]) == 0)
			count++;
		i++;
		free_2d_array(env_var);
	}
	array_backup = (char **)malloc((i - count + 1) * sizeof(char *));
	return (array_backup);
}

static char	**save_in_array_backup(char **array, char **array_backup,
		char *str_delete)
{
	int		j;
	int		g;
	char	**env_var;

	j = 0;
	g = 0;
	while (array[j])
	{
		env_var = ft_split(array[j], '=');
		if (ft_strcmp(str_delete, env_var[0]) != 0)
		{
			array_backup[g] = ft_strdup(array[j]);
			g++;
		}
		j++;
	}
	array_backup[g] = NULL;
	return (array_backup);
}

char	**delete_string_array(char **array, char *str_delete)
{
	char	**array_backup;
	char	**env_var;
	int		i;

	array_backup = allocate_mem_array_backup(array, array_backup, str_delete);
	array_backup = save_in_array_backup(array, array_backup, str_delete);
	free_2d_array(array);
	i = 0;
	while (array_backup[i])
		i++;
	array = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (array_backup[i])
	{
		array[i] = ft_strdup(array_backup[i]);
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	execute_unset_command(t_info *structure)
{
	int	i;
	int	l;

	if (!structure->table->arr[1])
		return ;
	else
	{
		if (check_env_variable(structure->envp, structure) == 1)
		{
			structure->envp = delete_string_array(structure->envp,
					structure->table->arr[1]);
			structure->envp_export = delete_string_array(structure->envp_export,
					structure->table->arr[1]);
		}
		else if (check_env_variable(structure->envp_export, structure) == 1)
			structure->envp_export = delete_string_array(structure->envp_export,
					structure->table->arr[1]);
		else
			return ;
	}
}
