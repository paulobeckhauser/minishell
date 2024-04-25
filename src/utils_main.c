/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:14:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 22:41:25 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	store_last_path(t_info *structure)
{
	char	*curr_path;
	char	*str;

	str = NULL;
	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
	{
		if (structure->folder != NULL)
		{
			str = ft_strdup(structure->folder);
			if (str == NULL)
				mem_alloc_protection();
			else
			{
				free(structure->folder);
				structure->folder = get_parent_folder(str);
				free(str);
			}
		}
	}
	free(curr_path);
}
