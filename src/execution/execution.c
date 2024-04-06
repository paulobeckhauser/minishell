/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/06 16:33:01 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	execution(t_info *structure)
{
	get_number_commands(structure);
	store_commands(structure);
	store_path_commands(structure);
	if (structure->table->type == BUILTIN_CMD
		&& structure->number_commands == 1)
		builtin_execution(structure);
	else
		pipes_implementation(structure);
	return (true);
}
