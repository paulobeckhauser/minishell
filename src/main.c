/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 13:13:17 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	t_info		structure;
	char cwd[PATH_MAX];

	char *curr_path;


	// int i;

	if (argc == 1)
	{
		(void)argv;
		
		init_vars(&structure);
		store_envp(envp, &structure);


		structure.folder = NULL;
		structure.folder_deleted = 0;

		char *str;
		
		while (1)
		{
			curr_path= getcwd(cwd, sizeof(cwd));
			if (curr_path == NULL)
			{
				str = ft_strdup(structure.folder);
				structure.folder = get_parent_folder(str);				
			}
			if (!parser(&structure, &prompt))
				continue;
			else
			{
				execution(&structure);
				free_cmd_table(&structure);
			}

		}
		// free_2d_array(structure.envp);
		// free_2d_array(structure.envp_export);
		// free_2d_array(structure.envp_sorted);
		// free_2d_array(structure.commands);
		// free_2d_array(structure.path_commands);
		// free_2d_int_array(structure.fds_pipes);
		free_exec_variables(&structure);
	}
	return (0);
}
