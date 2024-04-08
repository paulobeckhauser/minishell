/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/08 13:55:10 by pabeckha         ###   ########.fr       */
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
		get_path_env(&structure);
		while (1)
		{
			if (!parser(&structure, &prompt))
				continue;
			else
			{
				// // printf("%s\n", structure.table->arr[0]);
				// if ( (ft_strcmp(structure.table->arr[0], "echo") == 0) && ft_strcmp(structure.table->arr[1], "$?") == 0)
				// {
				// 	printf("here\n");
				// 	printf("%d\n", structure.last_exit_status);
				// 	// printf("AAAAA\n");
				// }

				// else
				// {
				execution(&structure);
					
				// }
			}

			


			
			
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
