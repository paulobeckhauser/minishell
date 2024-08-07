/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:34 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:57:10 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: allocate_mem_path
 * ----------------------------
 * Allocates memory for the PATH environment variable.
 * 
 * structure: The main structure containing all necessary data for execution.
 * i: The index of the environment variable in the envp_export array.
 * j: The index to start from within the environment variable string.
 * 
 * Returns the size of the allocated memory.
 */
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
	{
		perror("Memory allocation failed\n");
		structure->last_exit_status = EXIT_FAILURE;
		return (0);
	}
	return (size_alloc);
}

/* Function: store_path
 * ---------------------
 * Stores the PATH environment variable in the allocated memory.
 * 
 * i: The index of the environment variable in the envp_export array.
 * j: The index to start from within the environment variable string.
 * structure: The main structure containing all necessary data for execution.
 * size_alloc: The size of the allocated memory.
 */
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

/* Function: init_int_vars
 * ------------------------
 * Initializes integer variables to 0.
 * 
 * i: Pointer to the index of the environment variable.
 * j: Pointer to the index within the environment variable string.
 * count: Pointer to the count of found PATH variables.
 */
static void	init_int_vars(int *i, int *j, int *count)
{
	*i = 0;
	*j = 0;
	*count = 0;
}

/* Function: store_path_env
 * -------------------------
 * Extracts and stores the PATH environment variable.
 * 
 * structure: The main structure containing all necessary data for execution.
 * i: The index of the environment variable in the envp_export array.
 */
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

/* Function: get_path_env
 * -----------------------
 * Retrieves the PATH environment variable from the envp_export array.
 * 
 * structure: The main structure containing all necessary data for execution.
 * 
 * Returns the count of PATH variables found and stored.
 */
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