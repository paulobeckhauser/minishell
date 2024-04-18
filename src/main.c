/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 17:09:35 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;


// static void free_var_pid(t_info *structure)
// {
// 	if (!structure->pid)
// 		return ;
// 	free(structure->pid);
// }

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
			}
				
		}
		free_exec_variables(&structure);
	}
	return (0);
}
