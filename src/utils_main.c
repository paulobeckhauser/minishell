/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:14:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:37:17 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Function: init_vars
 * -------------------
 * Initializes all the variables in the t_info structure to their default values.
 * 
 * structure: A pointer to the t_info structure whose variables are to be initialized.
 * 
 * This function sets all pointer variables within the structure to NULL and all integer
 * variables to 0. It also initializes the folder and folder_deleted variables to NULL and 0,
 * respectively. It is typically called at the start of the program to ensure that all
 * variables are in a known state before they are used.
 */
void	init_vars(t_info *structure)
{
	structure->envp = NULL;
	structure->envp_export = NULL;
	structure->envp_sorted = NULL;
	structure->is_builtin = 0;
	structure->path_env = NULL;
	structure->number_commands = 0;
	structure->commands = NULL;
	structure->possible_paths = NULL;
	structure->path_commands = NULL;
	structure->fds_pipes = NULL;
	structure->pid = 0;
	structure->has_value_envp = 0;
	structure->number_equal_sign = 0;
	structure->count_number_signs = 0;
	structure->count_equal_sign = 0;
	structure->last_exit_status = 0;
	structure->folder = NULL;
	structure->folder_deleted = 0;
}

/* Function: store_last_path
 * -------------------------
 * Stores the last accessed path in the t_info structure.
 * 
 * structure: A pointer to the t_info structure where the last path is to be stored.
 * 
 * This function attempts to get the current working directory using getcwd and stores
 * it in the structure. If getcwd returns NULL, indicating an error, it instead stores
 * the parent folder of the last stored folder by duplicating the folder string and then
 * getting its parent folder. This is a fallback mechanism to ensure the program has a
 * valid path to work with even in case of errors. It also ensures to free the temporary
 * string used for this operation.
 */
void	store_last_path(t_info *structure)
{
	char	*curr_path;
	char	*str;
	char	cwd[PATH_MAX];

	curr_path = getcwd(cwd, sizeof(cwd));
	if (curr_path == NULL)
	{
		str = ft_strdup(structure->folder);
		structure->folder = get_parent_folder(str);
		free(str);
	}
}