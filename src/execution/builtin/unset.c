/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:53:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:50:32 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: is_unset_command
 * --------------------------
 * Checks if the given command is the 'unset' command.
 * 
 * command: A pointer to an array of strings representing the command and its arguments.
 * 
 * Returns 1 (true) if the first string in the command array is "unset", otherwise returns 0 (false).
 */
int	is_unset_command(char **command)
{
	return (ft_strcmp(command[0], "unset") == 0);
}

/* Function: allocate_mem_array_backup
 * -----------------------------------
 * Allocates memory for a backup array excluding the variable to be deleted.
 * 
 * array: The original array of environment variables.
 * array_backup: The backup array to be filled with variables except the one to delete.
 * str_delete: The name of the variable to delete.
 * 
 * Returns a pointer to the newly allocated backup array.
 */
static char	**allocate_mem_array_backup(char **array, char **array_backup,
		char *str_delete)
{
	int		i;
	int		count;
	char	**env_var;

	i = 0;
	count = 0;
	while (array[i])
	{
		env_var = ft_split(array[i], '=');
		if (ft_strcmp(str_delete, env_var[0]) == 0)
			count++;
		i++;
		free_2d_array(env_var);
	}
	array_backup = (char **)malloc((i - count + 1) * sizeof(char *));
	if (array_backup == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return (array_backup);
}

/* Function: save_in_array_backup
 * ------------------------------
 * Copies the original array to the backup array excluding the variable to be deleted.
 * 
 * array: The original array of environment variables.
 * array_backup: The backup array to be filled.
 * str_delete: The name of the variable to delete.
 * 
 * Returns a pointer to the filled backup array.
 */
static char	**save_in_array_backup(char **array, char **array_backup,
		char *str_delete)
{
	int		i;
	int		j;
	char	**env_var;

	i = 0;
	j = 0;
	env_var = NULL;
	while (array[i])
	{
		env_var = ft_split(array[i], '=');
		if (ft_strcmp(str_delete, env_var[0]) != 0)
		{
			array_backup[j] = ft_strdup(array[i]);
			j++;
		}
		i++;
		free_2d_array(env_var);
	}
	array_backup[j] = NULL;
	return (array_backup);
}

/* Function: delete_string_array
 * -----------------------------
 * Deletes a variable from the environment variables array.
 * 
 * array: The original array of environment variables.
 * str_delete: The name of the variable to delete.
 * 
 * Returns a new array with the specified variable removed.
 */
char	**delete_string_array(char **array, char *str_delete)
{
	char	**array_backup;
	int		i;

	array_backup = NULL;
	array_backup = allocate_mem_array_backup(array, array_backup, str_delete);
	array_backup = save_in_array_backup(array, array_backup, str_delete);
	free_2d_array(array);
	i = 0;
	while (array_backup[i])
		i++;
	array = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (array_backup[i])
	{
		array[i] = ft_strdup(array_backup[i]);
		i++;
	}
	array[i] = NULL;
	free_2d_array(array_backup);
	return (array);
}

/* Function: execute_unset_command
 * -------------------------------
 * Executes the 'unset' command by removing the specified environment variable.
 * 
 * structure: A pointer to the main structure containing environment variables and other data.
 * 
 * This function checks if there is a variable to unset. If so, it removes the variable from both
 * the environment variables array and the export array. It handles the case where the variable
 * might not exist in one of the arrays.
 */
void	execute_unset_command(t_info *structure)
{
	if (!structure->table->arr[1])
		return ;
	else
	{
		if (check_env_variable(structure) == 1)
		{
			structure->envp = delete_string_array(structure->envp,
					structure->table->arr[1]);
			structure->envp_export = delete_string_array(structure->envp_export,
					structure->table->arr[1]);
		}
		else if (check_env_variable(structure) == 1)
			structure->envp_export = delete_string_array(structure->envp_export,
					structure->table->arr[1]);
		else
			return ;
	}
}