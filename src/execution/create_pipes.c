/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:30:39 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/08 17:25:38 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_pipes(t_info *structure)
{
	int	i;

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
		structure->fds_pipes[i] = (int *)ft_calloc(2 + 1, sizeof(int));
		if (structure->fds_pipes[i] == NULL)
		{
			perror("Memory allocation failed");
			return ;
		}
		if (pipe(structure->fds_pipes[i]) == -1)
			perror("Pipe creation failed");
		i++;
	}
	structure->fds_pipes[i] = NULL;
}
