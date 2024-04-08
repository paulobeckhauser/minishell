/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:38:08 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/05 21:53:20 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	**allocate_mem_backup_array(char **array, char **backup_array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	backup_array = (char **)malloc((i + 1) * sizeof(char *));
	if (backup_array == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return (backup_array);
}

static char	**allocate_mem_array(char **array, char **backup_array)
{
	int	i;

	i = 0;
	while (backup_array[i])
		i++;
	array = (char **)malloc((i + 2) * sizeof(char *));
	if (array == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return (array);
}

static char	**add_variable_to_array(char *str_add, char **array)
{
	char	**backup_array;
	int		i;

	backup_array = NULL;
	backup_array = allocate_mem_backup_array(array, backup_array);
	i = 0;
	while (array[i])
	{
		backup_array[i] = ft_strdup(array[i]);
		i++;
	}
	free_2d_array(array);
	array = allocate_mem_array(array, backup_array);
	i = 0;
	while (backup_array[i])
	{
		array[i] = ft_strdup(backup_array[i]);
		i++;
	}
	array[i] = ft_strdup(str_add);
	i++;
	array[i] = NULL;
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
