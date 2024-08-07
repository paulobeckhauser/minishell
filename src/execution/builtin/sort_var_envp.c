/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_var_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:56:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:49:47 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: get_lenght
 * --------------------
 * Calculates the length of the envp array.
 * 
 * envp: The environment variables array.
 * 
 * Returns the number of elements in the envp array.
 */
static int	get_lenght(char **envp)
{
	int	length;

	length = 0;
	while (envp[length])
		length++;
	return (length);
}

/* Function: str_compare
 * ---------------------
 * Finds the index of the smallest string in envp array from index j to length.
 * 
 * j: Starting index for comparison.
 * length: Total number of elements in envp.
 * j_min: Index of the current smallest string.
 * envp: The environment variables array.
 * 
 * Returns the index of the smallest string in the specified range.
 */
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

/* Function: allocate_mem_sort_var
 * -------------------------------
 * Allocates memory for the sorted environment variables array and copies the content from the original array.
 * 
 * structure: A pointer to the main structure containing environment variables and other data.
 * 
 * This function allocates memory for the sorted version of the environment variables array and then
 * duplicates each string from the original array to the sorted array.
 */
void	allocate_mem_sort_var(t_info *structure)
{
	int	i;
	int	len;

	len = 0;
	while (structure->envp_export[len])
		len++;
	structure->envp_sorted = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	while (structure->envp_export[i])
	{
		structure->envp_sorted[i] = ft_strdup(structure->envp_export[i]);
		i++;
	}
	structure->envp_sorted[i] = NULL;
}

/* Function: selectiton_sort_variables
 * -----------------------------------
 * Sorts the environment variables array using the selection sort algorithm.
 * 
 * envp: The environment variables array to be sorted.
 * 
 * This function iterates over the envp array and for each element, finds the smallest string
 * in the remaining array. If the smallest string is not the current element, it swaps them.
 */
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