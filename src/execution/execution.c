/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 12:42:16 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	execution(t_info *structure)
{
	int test;
	int i;
	char cwd[PATH_MAX];
	
	i = 0;

	test = 0;

	handle_key_combos_execution();
	get_number_commands(structure);


	structure->folder = getcwd(cwd, sizeof(cwd));
	if (structure->table->type == BUILTIN_CMD && structure->number_commands == 1)
		builtin_execution(structure);
	else
	{
		test = get_path_env(structure);

		if (test == 0)
		{
			i = 0;
			while (structure->table)
				structure->table = structure->table->next;
			structure->last_exit_status = EX_COMM_NOTFOUND;
		}
		else
		{
			store_commands(structure);
			store_path_commands(structure);
			pipes_implementation(structure);
		}

		
	}
	return (true);
}
