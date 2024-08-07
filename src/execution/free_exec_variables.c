/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:01:02 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:54:57 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: free_exec_variables
 * ------------------------------
 * Frees all dynamically allocated memory used during command execution.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function is responsible for freeing all the dynamically allocated memory that was
 * used during the execution of commands. It frees the environment variables arrays,
 * the commands array, the path commands array, and the file descriptors for pipes.
 */
void	free_exec_variables(t_info *structure)
{
	// Free the environment variables array
	free_2d_array(structure->envp);
	// Free the exported environment variables array
	free_2d_array(structure->envp_export);
	// Free the sorted environment variables array
	free_2d_array(structure->envp_sorted);
	// Free the commands array
	free_2d_array(structure->commands);
	// Free the path commands array
	free_2d_array(structure->path_commands);
	// Free the file descriptors for pipes
	free_2d_int_array(structure->fds_pipes);
}