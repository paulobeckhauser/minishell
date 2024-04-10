/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/10 22:21:37 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	execution(t_info *structure)
{
	int test;

	test = 0;

	handle_key_combos_execution();
	get_number_commands(structure);
	if (structure->table->type == BUILTIN_CMD && structure->number_commands == 1)
		builtin_execution(structure);
	else
	{
		test = get_path_env(structure);

		if (test == 0)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(structure->table->arr[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
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
