/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:47:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 16:21:12 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: free_2d_array
 * ------------------------
 * Frees a dynamically allocated 2D array of characters.
 * 
 * array: A pointer to the first element of the array to be freed.
 * 
 * This function iterates through each element of the array, freeing each string
 * individually before finally freeing the array itself. It then sets the pointer
 * to the array to NULL to avoid dangling pointers.
 */
void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	array = NULL;
}

/* Function: free_2d_int_array
 * ----------------------------
 * Frees a dynamically allocated 2D array of integers.
 * 
 * array: A pointer to the first element of the array to be freed.
 * 
 * Similar to free_2d_array, this function iterates through each element of the
 * array, freeing each sub-array of integers individually before freeing the array
 * itself. It then sets the pointer to the array to NULL to prevent dangling pointers.
 */
void	free_2d_int_array(int **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	array = NULL;
}