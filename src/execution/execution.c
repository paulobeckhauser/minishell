/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:49 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	preparation_for_execution(t_info *structure)
{
	handle_key_combos_execution();
	get_number_commands(structure);
}

static void	pipeline_execution(t_info *structure)
{
	store_commands(structure);
	store_path_commands(structure);
	pipes_implementation(structure);
}

static void	print_err_no_path(t_info *structure)
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

bool	execution(t_info *structure)
{
	int		flag_cur_folder;
	char	cwd[PATH_MAX];

	flag_cur_folder = 0;
	structure->folder = getcwd(cwd, sizeof(cwd));
	preparation_for_execution(structure);
	if (structure->table->type == BUILTIN_CMD
		&& structure->number_commands == 1)
		builtin_execution(structure);
	else
	{
		flag_cur_folder = get_path_env(structure);
		if (flag_cur_folder == 0)
			print_err_no_path(structure);
		else
			pipeline_execution(structure);
	}
	return (true);
}
