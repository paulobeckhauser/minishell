/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 16:21:05 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pipeline_execution(t_info *structure)
{
	store_commands(structure);
	store_path_commands(structure);
	pipes_implementation(structure);
}

bool	execution(t_info *structure)
{
	int		flag_cur_folder;
	char	cwd[PATH_MAX];

	flag_cur_folder = 0;
	handle_key_combos_execution();
	get_number_commands(structure);
	// flag_cur_folder = get_path_env(structure);
	structure->folder = getcwd(cwd, sizeof(cwd));
	if (structure->table->type == BUILTIN_CMD
		&& structure->number_commands == 1)
		builtin_execution(structure);
	else
	{
		// flag_cur_folder = get_path_env(structure);
		// printf("The flag is: %d\n", flag_cur_folder);
		// if (flag_cur_folder == 0)
		if (get_path_env(structure) == 0)
		{
			while (structure->table)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(structure->table->arr[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				structure->table = structure->table->next;
			}
			structure->last_exit_status = EX_COMM_NOTFOUND;
		}
		else
			pipeline_execution(structure);
	}
	return (true);
}
