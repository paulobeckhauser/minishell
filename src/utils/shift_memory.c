/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:35:26 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:33:18 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: shift_strings_left
 * ----------------------------
 * Shifts all strings in an array one position to the left from a given index.
 * 
 * arr: The array of strings to be shifted.
 * index: The starting index from which to begin shifting.
 * size: The total number of elements in the array.
 * 
 * Returns 1 if the shift is successful, 0 if the array has only one element.
 * 
 * The function frees the string at the specified index, then uses ft_memmove
 * to shift all subsequent strings one position to the left. The last position
 * in the array is set to NULL to indicate the end of the valid strings. This
 * operation is useful for removing an element from an array of strings while
 * maintaining the order of the remaining elements.
 */
int	shift_strings_left(char **arr, int index, int size)
{
	free(arr[index]);
	if (size == 1)
		return (0);
	ft_memmove(&arr[index], &arr[index + 1],
		(size - index - 1) * sizeof(char *));
	arr[size - 1] = NULL;
	return (1);
}