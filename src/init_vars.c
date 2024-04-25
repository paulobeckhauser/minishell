/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:14:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 12:33:17 by sfrankie         ###   ########.fr       */
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
}

void	store_last_path(t_info *structure)
{
	char	*curr_path;
	char	*str;
	char	cwd[PATH_MAX];

	curr_path = getcwd(cwd, sizeof(cwd));
	if (curr_path == NULL)
	{
		str = ft_strdup(structure->folder);
		if (str == NULL)
			mem_alloc_protection();
		structure->folder = get_parent_folder(str);
	}
	free(str);
}
