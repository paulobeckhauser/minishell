/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parent_folder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:00:27 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/21 14:17:33 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: get_size_arr
 * ----------------------
 * Counts the number of elements in a string array.
 * 
 * array: The string array whose elements are to be counted.
 * 
 * Returns the number of elements in the array.
 */
static int	get_size_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/* Function: copy_str
 * ------------------
 * Copies a string up to a specified index into a new string, frees the original string,
 * and duplicates the new string into the original string's memory space.
 * 
 * updated_str: The original string to be copied and updated.
 * str_new: The new string where the original string is copied to.
 * i: The index up to which the original string is copied.
 * 
 * Returns the updated string.
 */
static char	*copy_str(char *updated_str, char *str_new, int i)
{
	int	iter;

	iter = 0;
	while (updated_str[iter] && iter <= i)
	{
		str_new[iter] = updated_str[iter];
		iter++;
	}
	str_new[iter] = '\0';
	free(updated_str);
	updated_str = ft_strdup(str_new);
	return (updated_str);
}

/* Function: iterate_copy
 * ----------------------
 * Iteratively copies segments of the original string, excluding parts of the path
 * that do not match the access rights, and updates the string accordingly.
 * 
 * arr: The array of path segments.
 * elem: The current element of the array being processed.
 * updated_str: The current state of the string being updated.
 * str: The original string.
 * 
 * Returns the updated string after removing the non-matching path segment.
 */
static char	*iterate_copy(char **arr, int elem, char *updated_str, char *str)
{
	char	*str_path;
	char	*str_new;
	int		i;
	int		j;

	str_path = ft_strjoin("/", arr[elem]);
	str_new = malloc(ft_strlen(updated_str) - ft_strlen(arr[elem])
			- ft_strlen("/") + 1);
	if (!str_new)
		return (NULL);
	i = ft_strlen(updated_str) - 1;
	j = ft_strlen(str_path) - 1;
	while (str[i] && str_path[j] && str[i] == str_path[j])
	{
		i--;
		j--;
	}
	updated_str = copy_str(updated_str, str_new, i);
	free(str_new);
	free(str_path);
	return (updated_str);
}

/* Function: get_parent_folder
 * ---------------------------
 * Finds the parent folder of a given path that has the required access rights.
 * 
 * str: The path for which the parent folder is to be found.
 * 
 * This function splits the given path into segments, iteratively checks each segment
 * from the end for access rights, and updates the path to exclude segments without
 * the required access rights. It returns the updated path that meets the access
 * requirements.
 * 
 * Returns the path of the parent folder with the required access rights.
 */
char	*get_parent_folder(char *str)
{
	char	**arr;
	int		elem;
	char	*updated_str;

	arr = ft_split(str, '/');
	elem = get_size_arr(arr) - 1;
	updated_str = ft_strdup(str);
	while (elem > 0)
	{
		if (access(updated_str, X_OK) == 0)
			break ;
		updated_str = iterate_copy(arr, elem, updated_str, str);
		elem--;
	}
	return (updated_str);
}