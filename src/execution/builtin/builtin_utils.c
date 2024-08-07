/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:10:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:38:46 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: allocate_str_temp
 * ---------------------------
 * Allocates memory for a temporary string used to store environment variable names.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * str_temp: The temporary string to be allocated.
 * i: The index of the environment variable in the envp_export array.
 * 
 * Returns a pointer to the allocated temporary string.
 * 
 * This function calculates the length of the environment variable name up to the '=' character,
 * allocates memory for a temporary string of that length plus one for the null terminator, and
 * returns a pointer to this allocated memory. If memory allocation fails, it prints an error message
 * and exits the program.
 */
char	*allocate_str_temp(t_info *structure, char *str_temp, int i)
{
	int	len;

	len = 0;
	while (structure->envp_export[i][len]
		&& structure->envp_export[i][len] != '=')
		len++;
	str_temp = (char *)malloc((len + 1) * sizeof(char));
	if (str_temp == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return (str_temp);
}

/* Function: save_str_temp
 * -----------------------
 * Copies the name of an environment variable into a temporary string.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * i: The index of the environment variable in the envp_export array.
 * str_temp: The temporary string where the environment variable name will be copied.
 * 
 * Returns a pointer to the temporary string with the environment variable name.
 * 
 * This function iterates through the characters of the environment variable name up to the '=' character,
 * copying each character into the temporary string. It then null-terminates the temporary string and returns
 * a pointer to it.
 */
char	*save_str_temp(t_info *structure, int i, char *str_temp)
{
	int	j;

	j = 0;
	while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
	{
		str_temp[j] = structure->envp_export[i][j];
		j++;
	}
	str_temp[j] = '\0';
	return (str_temp);
}

/* Function: check_env_variable
 * ----------------------------
 * Checks if a given environment variable exists in the envp_export array.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * Returns 1 if the environment variable exists, 0 otherwise.
 * 
 * This function iterates through the envp_export array, allocating and saving each environment variable name
 * into a temporary string. It then compares the temporary string with the target environment variable name.
 * If a match is found, it frees the temporary string, sets the check_exist flag to 1, and breaks the loop.
 * If no match is found, it continues to the next environment variable. The function returns the check_exist flag.
 */
int	check_env_variable(t_info *structure)
{
	int		check_exist;
	int		i;
	char	*str_temp;

	check_exist = 0;
	i = 0;
	while (structure->envp_export[i])
	{
		str_temp = allocate_str_temp(structure, str_temp, i);
		str_temp = save_str_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, structure->table->arr[1]) == 0)
		{
			free(str_temp);
			check_exist = 1;
			break ;
		}
		free(str_temp);
		i++;
	}
	return (check_exist);
}