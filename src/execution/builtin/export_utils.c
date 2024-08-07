/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:50:31 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:45:51 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: handle_equal_signs
 * -----------------------------
 * Replaces all but the first equal sign in the argument with a temporary character.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * This function is used when an export command argument contains more than one equal sign.
 * It ensures that only the first equal sign is treated as the delimiter between the variable
 * name and its value. All subsequent equal signs are temporarily replaced with a character
 * that is unlikely to be used in normal input (ASCII code 2 in this case).
 */
static void	handle_equal_signs(t_info *structure)
{
	int	first_equal_sign;
	int	i;

	first_equal_sign = 0;
	i = 0;
	if (structure->count_equal_sign > 1)
	{
		while (structure->table->arr[1][i]
			&& structure->table->arr[1][i] != '=')
		{
			i++;
		}
		if (structure->table->arr[1][i] == '=')
			first_equal_sign = i;
		i = 0;
		while (structure->table->arr[1][i])
		{
			if (i != first_equal_sign && structure->table->arr[1][i] == '=')
				structure->table->arr[1][i] = 2;
			i++;
		}
	}
}

/* Function: use_print_export_structure
 * ------------------------------------
 * Updates the environment variables after processing an export command.
 * 
 * structure: A pointer to the main structure containing environment variables.
 * array: The split variable name and value from the export command.
 * new_string: The new variable definition to add to the environment.
 * check_equal_sign: Indicates if the original command contained an equal sign.
 * 
 * This function removes the old variable definition from the environment (if it exists)
 * and adds the new definition. It then frees the memory allocated for the split array.
 */
static void	use_print_export_structure(t_info *structure, char **array,
		char *new_string, int check_equal_sign)
{
	structure->envp = delete_string_array(structure->envp, array[0]);
	structure->envp_export = delete_string_array(structure->envp_export,
			array[0]);
	add_to_envp(structure, new_string, check_equal_sign);
	free_2d_array(array);
}

/* Function: print_if_there_is_arg
 * --------------------------------
 * Handles the export command when there is an argument to process.
 * 
 * new_string: The new variable definition to add to the environment.
 * array: The split variable name and value from the export command.
 * structure: A pointer to the main structure containing environment variables.
 * check_equal_sign: Indicates if the original command contained an equal sign.
 * 
 * This function reconstructs the variable definition from the split name and value,
 * replacing any temporary characters with equal signs. It then updates the environment
 * variables using use_print_export_structure.
 */
static void	print_if_there_is_arg(char *new_string, char **array,
		t_info *structure, int check_equal_sign)
{
	int		i;
	char	*backup_string;

	i = 0;
	while (array[1][i])
	{
		if (array[1][i] == 2)
			array[1][i] = '=';
		i++;
	}
	backup_string = NULL;
	backup_string = ft_strjoin(array[0], "=");
	free(new_string);
	new_string = ft_strjoin(backup_string, array[1]);
	free(backup_string);
	use_print_export_structure(structure, array, new_string, check_equal_sign);
	free(new_string);
}

/* Function: replace_value_envp
 * -----------------------------
 * Processes the export command, updating the environment variables accordingly.
 * 
 * structure: A pointer to the main structure containing environment variables.
 * check_equal_sign: Indicates if the original command contained an equal sign.
 * 
 * This function first counts the number of equal signs in the command and handles
 * them if necessary. It then splits the command argument into the variable name and
 * value, processes the export command based on whether a value is provided, and updates
 * the environment variables.
 */
void	replace_value_envp(t_info *structure, int check_equal_sign)
{
	char	**array;
	char	*new_string;

	new_string = NULL;
	count_equal_sign(structure);
	handle_equal_signs(structure);
	array = ft_split(structure->table->arr[1], '=');
	if (array[1])
		print_if_there_is_arg(new_string, array, structure, check_equal_sign);
	else
	{
		new_string = ft_strjoin(array[0], "=");
		use_print_export_structure(structure, array, new_string,
			check_equal_sign);
	}
}