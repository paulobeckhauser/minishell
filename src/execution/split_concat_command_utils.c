/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_concat_command_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:49:45 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 16:00:56 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: ft_free
 * -----------------
 * Frees an array of strings and its contents.
 * 
 * strs: The array of strings to be freed.
 * count: The number of strings in the array.
 * 
 * Returns: NULL, to allow for easy error handling by setting pointers to NULL after freeing.
 */
void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

/* Function: check_and_free
 * ------------------------
 * Checks if the last allocated string in an array is NULL, indicating an allocation failure,
 * and frees the entire array if so.
 * 
 * array: The array of strings to check and potentially free.
 * j: The index of the last allocated string in the array.
 * 
 * Returns: NULL if the last string is NULL (indicating an error), or the original array otherwise.
 */
char	**check_and_free(char **array, int j)
{
	if (!(array[j]))
	{
		ft_free(array, j);
		return (NULL);
	}
	return (array);
}