/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 13:57:29 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	t_info		structure;

	if (argc == 1)
	{
		(void)argv;
		init_vars(&structure);
		store_envp(envp, &structure);


		structure.folder = NULL;
		structure.folder_deleted = 0;
		while (1)
		{
			store_last_path(&structure);
			if (!parser(&structure, &prompt))
				continue ;
			else
			{
				execution(&structure);
				free_cmd_table(&structure.table);
				free_2d_int_array(structure.fds_pipes);
				free_2d_array(structure.commands);
				free_2d_array(structure.path_commands);
				free(structure.path_env);
				free(structure.pid);
			}
				
		}
		free_exec_variables(&structure);
	}
	return (0);
}
