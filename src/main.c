/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/16 11:39:35 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	t_info		structure;
	char		cwd[PATH_MAX];
	char		*curr_path;
	char		*str;

	if (argc == 1)
	{
		(void)argv;
		init_vars(&structure);
		store_envp(envp, &structure);
		prompt.folder = NULL;
		structure.folder = NULL;
		structure.folder_deleted = 0;
		while (1)
		{
			store_last_path(&structure);
			if (!parser(&structure, &prompt))
				continue ;
			else
				execution(&structure);
		}
		free_exec_variables(&structure);
	}
	return (0);
}
