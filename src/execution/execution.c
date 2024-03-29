/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 19:30:25 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execution(t_info *structure, t_prompt *prompt)
{
	get_number_commands(structure);
	store_commands(structure);
	store_path_commands(structure);
	if (structure->table->type == BUILTIN_CMD
		&& structure->number_commands == 1)
		builtin_execution(structure);
	else
		pipes_implementation(structure);
}
