/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:38:08 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 13:05:43 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	**allocate_mem_backup_array(char **array, char **backup_array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	backup_array = ft_calloc(i + 1, sizeof(char *));
	if (backup_array == NULL)
		mem_alloc_protection();
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
		mem_alloc_protection();
	return (array);
}

static void	assign_data_to_array(char **array, char **backup_array,
	char *str_add)
{
	int	i;

	i = 0;
	while (backup_array[i])
	{
		array[i] = ft_strdup(backup_array[i]);
		if (array[i] == NULL)
			mem_alloc_protection();
		i++;
	}
	array[i] = ft_strdup(str_add);
	if (array[i] == NULL)
		mem_alloc_protection();
	i++;
	array[i] = NULL;
	free_2d_array(backup_array);
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
		if (backup_array[i] == NULL)
			mem_alloc_protection();
		i++;
	}
	backup_array[i] = NULL;
	free_2d_array(array);
	array = allocate_mem_array(array, backup_array);
	assign_data_to_array(array, backup_array, str_add);
	return (array);
}

void	add_to_envp(t_info *structure, char *str_add, int check_equal_sign)
{
	if (check_equal_sign == 1)
		structure->envp = add_variable_to_array(str_add, structure->envp);
	structure->envp_export = add_variable_to_array(str_add,
			structure->envp_export);
}
