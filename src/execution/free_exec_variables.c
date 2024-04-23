/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:01:02 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 22:27:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_exec_variables(t_info *structure)
{
	free_2d_array(structure->envp);
	free_2d_array(structure->envp_export);
	free_2d_array(structure->envp_sorted);
	free_2d_array(structure->commands);
	free_2d_array(structure->path_commands);
	free_2d_int_array(structure->fds_pipes);
	// free(structure->path_env);
}
