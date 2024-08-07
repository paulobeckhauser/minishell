/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:30:39 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:54:03 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: create_pipes
 * -----------------------
 * Allocates and initializes pipes for inter-process communication.
 * 
 * structure: A pointer to the main structure containing all necessary data for execution.
 * 
 * This function dynamically allocates memory for an array of pipes based on the number
 * of commands to be executed. Each command, except the last one, needs a pipe to the next
 * command for communication. It initializes these pipes and handles any errors in memory
 * allocation or pipe creation.
 */
void	create_pipes(t_info *structure)
{
	int	i;

	// Allocate memory for the array of pipe file descriptors
	structure->fds_pipes = (int **)ft_calloc((structure->number_commands),
			sizeof(int *));
	if (structure->fds_pipes == NULL)
	{
		perror("Memory allocation failed");
		return ;
	}
	i = 0;
	while (i < structure->number_commands - 1)
	{
		// Allocate memory for each pipe (2 file descriptors per pipe)
		structure->fds_pipes[i] = (int *)ft_calloc(2 + 1, sizeof(int));
		if (structure->fds_pipes[i] == NULL)
		{
			perror("Memory allocation failed");
			return ;
		}
		// Create the pipe and handle any errors
		if (pipe(structure->fds_pipes[i]) == -1)
			perror("Pipe creation failed");
		i++;
	}
	// Mark the end of the array with NULL for easier handling
	structure->fds_pipes[i] = NULL;
}