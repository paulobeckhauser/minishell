/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:32:54 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 16:03:07 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: allocate_memory_path_commands
 * ---------------------------------------
 * Allocates memory for the path_commands array within the t_info structure.
 * This array will store the full paths to the commands.
 * 
 * structure: A pointer to the t_info structure containing the command information.
 */
static void	allocate_memory_path_commands(t_info *structure)
{
	structure->path_commands = (char **)malloc((structure->number_commands + 1)
			* sizeof(char *));
	if (!structure->path_commands)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
}

/* Function: condition_dup
 * -----------------------
 * Duplicates the valid command path into the path_commands array.
 * 
 * structure: A pointer to the t_info structure containing the command information.
 * i: The index of the current command.
 * j: The index of the valid path in the possible_paths array.
 */
static void	condition_dup(t_info *structure, int i, int j)
{
	if (structure->possible_paths[j] != NULL)
		structure->path_commands[i] = ft_strdup(structure->possible_paths[j]);
	else
		structure->path_commands[i] = ft_strdup(structure->possible_paths[--j]);
}

/* Function: get_path_command
 * --------------------------
 * Determines the valid command path and stores it in the path_commands array.
 * 
 * structure: A pointer to the t_info structure containing the command information.
 * i: The index of the current command.
 * j: The index used to iterate through the possible_paths array.
 */
static void	get_path_command(t_info *structure, int i, int j)
{
	if (structure->possible_paths == NULL)
	{
		free(structure->path_env);
		free(structure->commands[i]);
	}
	else
	{
		j = 0;
		while (structure->possible_paths[j])
		{
			if (access(structure->possible_paths[j], X_OK) == 0)
				break ;
			j++;
		}
		condition_dup(structure, i, j);
	}
}

/* Function: store_path_commands
 * -----------------------------
 * Stores the full paths to the commands in the path_commands array.
 * 
 * structure: A pointer to the t_info structure containing the command information.
 */
void	store_path_commands(t_info *structure)
{
	int	i;
	int	j;

	allocate_memory_path_commands(structure);
	i = 0;
	j = 0;
	while (structure->commands[i])
	{
		if (access(structure->commands[i], X_OK) == 0)
			structure->path_commands[i] = ft_strdup(structure->commands[i]);
		else
		{
			structure->possible_paths = split_concat(structure->path_env,
					':', structure->commands[i]);
			get_path_command(structure, i, j);
			free_2d_array(structure->possible_paths);
		}
		i++;
	}
	structure->path_commands[i] = NULL;
}