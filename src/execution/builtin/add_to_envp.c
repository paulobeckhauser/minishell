/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:38:08 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 20:29:30 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: allocate_mem_backup_array
 * -----------------------------------
 * Allocates memory for a backup array that will temporarily hold the contents of another array.
 * 
 * array: The original array whose contents are to be backed up.
 * backup_array: The backup array where the contents of the original array will be stored.
 * 
 * Returns a pointer to the newly allocated backup array.
 * 
 * This function counts the number of elements in the original array and allocates memory
 * for the backup array accordingly. It exits the program with an error message if memory
 * allocation fails.
 */
static char	**allocate_mem_backup_array(char **array, char **backup_array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	backup_array = ft_calloc(i + 1, sizeof(char *));
	if (backup_array == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return (backup_array);
}

/* Function: allocate_mem_array
 * ----------------------------
 * Allocates memory for an array that will hold the contents of a backup array plus one additional element.
 * 
 * array: The original array that will be replaced by the newly allocated array.
 * backup_array: The backup array whose contents will be copied into the newly allocated array.
 * 
 * Returns a pointer to the newly allocated array.
 * 
 * This function counts the number of elements in the backup array and allocates memory
 * for a new array that can hold one additional element. It exits the program with an
 * error message if memory allocation fails.
 */
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

/* Function: add_variable_to_array
 * -------------------------------
 * Adds a new variable to an array.
 * 
 * str_add: The string to be added to the array.
 * array: The original array to which the string will be added.
 * 
 * Returns a pointer to the array with the new string added.
 * 
 * This function creates a backup of the original array, frees the original array,
 * allocates memory for a new array that can hold one additional element, copies the
 * contents of the backup array to the new array, adds the new string, and then frees
 * the backup array.
 */
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
	backup_array[i] = NULL;
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

/* Function: add_to_envp
 * ---------------------
 * Adds a new variable to the environment variables array and the export array.
 * 
 * structure: The main structure containing the environment variables and export arrays.
 * str_add: The string to be added to the arrays.
 * check_equal_sign: A flag indicating whether the string should be added to the environment variables array.
 * 
 * This function adds the new string to the environment variables array if the check_equal_sign flag is set,
 * and to the export array regardless of the flag. It ensures that the new string is added to both arrays
 * where applicable.
 */
void	add_to_envp(t_info *structure, char *str_add, int check_equal_sign)
{
	if (check_equal_sign == 1)
		structure->envp = add_variable_to_array(str_add, structure->envp);
	structure->envp_export = add_variable_to_array(str_add,
			structure->envp_export);
}