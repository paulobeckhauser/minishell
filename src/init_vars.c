/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:14:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/06 19:06:30 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void init_vars(t_info *structure)
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

    // structure->exit_status = 0;
	structure->last_exit_status = 0;
    
    
}
