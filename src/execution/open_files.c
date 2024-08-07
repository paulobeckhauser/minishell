/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:57:30 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:58:07 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: open_files
 * ---------------------
 * Opens input and output files for a command based on priority.
 * 
 * table: The command table containing file information and priorities.
 * 
 * Returns 1 if all files were successfully opened, 0 if an error occurred.
 */
int	open_files(t_cmd *table)
{
	/* If input priority is set, open input files first, then output files. */
	if (table->in_prio)
	{
		if (!open_in_files(table) || !open_out_files(table))
			return (0);
	}
	else
	{
		/* If input priority is not set, open output files first, then input files. */
		if (!open_out_files(table) || !open_in_files(table))
			return (0);
	}
	return (1);
}