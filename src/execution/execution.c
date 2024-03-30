/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/30 12:32:55 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execution(t_info *structure, t_prompt *prompt)
{
	int fd_test;

	if (structure->table->in.heredoc)
	{
		fd_test = open("tmp/heredoc_tmp", O_RDONLY);
		structure->table->in.fd = fd_test;
	}
	get_number_commands(structure);
	store_commands(structure);
	store_path_commands(structure);
	if (structure->table->type == BUILTIN_CMD
		&& structure->number_commands == 1)
		builtin_execution(structure);
	else
		pipes_implementation(structure);
}
