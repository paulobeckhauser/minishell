/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:57:30 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/19 19:32:05 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_files(t_cmd *table)
{
	if (table->in_prio)
	{
		if (!open_in_files(table) || !open_out_files(table))
			return (0);
	}
	else
	{
		if (!open_out_files(table) || !open_in_files(table))
			return (0);
	}
	return (1);
}
