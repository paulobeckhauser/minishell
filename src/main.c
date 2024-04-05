/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/05 22:26:25 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	t_info		structure;

	if (argc == 1)
	{
		(void)argv;
		store_envp(envp, &structure);
		get_path_env(&structure);
		// printf("%s\n", structure.path_env);
		while (1)
		{
			if (!parser(&structure, &prompt))
				continue ;
			else
				execution(&structure);
		}
		
	// 	free_2d_array(structure.envp);
	// 	free_2d_array(structure.envp_export);
	// 	free_2d_array(structure.envp_sorted);
	// 	free_2d_array(structure.commands);
	// 	free_2d_array(structure.path_commands);
	// 	free_2d_int_array(structure.fds_pipes);
	}
	return (0);
}
