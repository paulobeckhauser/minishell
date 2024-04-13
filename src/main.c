/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/12 21:49:31 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	t_info		structure;
	char cwd[PATH_MAX];

	char *test;

	if (argc == 1)
	{
		(void)argv;
		
		init_vars(&structure);
		store_envp(envp, &structure);



		
		while (1)
		{
			
			// test = getcwd(cwd, sizeof(cwd));
			// // printf("%s\n", test);

			// if (getcwd(cwd, sizeof(cwd)) == NULL) {
			// 	// The current directory doesn't exist. Print an error message and skip this command.
			// 	perror("minishell");
			// 	continue;
			// }
			
			
			if (!parser(&structure, &prompt))
				continue;
			else
				execution(&structure);
		}
		free_2d_array(structure.envp);
		free_2d_array(structure.envp_export);
		free_2d_array(structure.envp_sorted);
		free_2d_array(structure.commands);
		free_2d_array(structure.path_commands);
		free_2d_int_array(structure.fds_pipes);
	}
	return (0);
}
