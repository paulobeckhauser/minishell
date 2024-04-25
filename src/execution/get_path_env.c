/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:34 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 12:00:10 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	allocate_mem_path(t_info *structure, int i, int j)
{
	int	size_alloc;

	size_alloc = 0;
	while (structure->envp_export[i][j])
	{
		size_alloc++;
		j++;
	}
	structure->path_env = (char *)malloc((size_alloc + 1) * sizeof(char));
	if (structure->path_env == NULL)
		mem_alloc_protection();
	return (size_alloc);
}

static void	store_path(int i, int j, t_info *structure, int size_alloc)
{
	int	g;

	g = 0;
	while (structure->envp_export[i][j] && g < size_alloc)
	{
		structure->path_env[g] = structure->envp_export[i][j];
		j++;
		g++;
	}
	structure->path_env[g] = '\0';
}

static void	init_int_vars(int *i, int *j, int *count)
{
	*i = 0;
	*j = 0;
	*count = 0;
}

static void	store_path_env(t_info *structure, int i)
{
	int	j;
	int	size_alloc;

	j = 0;
	while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
		j++;
	j++;
	size_alloc = allocate_mem_path(structure, i, j);
	store_path(i, j - 1, structure, size_alloc);
}

int	get_path_env(t_info *structure)
{
	int		i;
	int		j;
	char	*str_temp;
	int		count;

	if (structure->envp_export == NULL)
		return (0);
	init_int_vars(&i, &j, &count);
	structure->path_env = NULL;
	while (structure->envp_export[i])
	{
		str_temp = allocate_str_temp(structure, str_temp, i);
		str_temp = save_str_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, "PATH") == 0)
		{
			count++;
			store_path_env(structure, i);
		}
		free(str_temp);
		i++;
	}
	return (count);
}
