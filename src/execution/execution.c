/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/26 20:26:38 by pabeckha         ###   ########.fr       */
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
	t_cmd	*head;

	head = structure->table;
	while (structure->table)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(structure->table->arr[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		structure->table = structure->table->next;
	}
	structure->table = head;
	structure->last_exit_status = EX_COMM_NOTFOUND;
}

bool	execution(t_info *structure)
{
	int		flag_cur_folder;

	flag_cur_folder = 0;
	free(structure->folder);
	structure->folder = getcwd(NULL, 0);
	preparation_for_execution(structure);
	if (structure->table->type == BUILTIN_CMD
		&& structure->number_commands == 1)
		builtin_execution(structure);
	else
	{
		flag_cur_folder = get_path_env(structure);
		// printf("The value is: %d\n", flag_cur_folder);
		
		if (flag_cur_folder == 0)
			print_err_no_path(structure);
		else
		{
			pipeline_execution(structure);
			// free(structure->path_env);		
		}
	}
	return (true);
}
