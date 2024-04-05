/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/05 18:44:07 by sfrankie         ###   ########.fr       */
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
		store_envp(envp, &structure);


		// int i;
		// i =0;
		// char	*str_temp;
		// while(structure.envp_export[i])
		// {
		// 	int j;
		// 	j = 0;
		// 	str_temp = allocate_str_temp(&structure, str_temp, i);
		// 	str_temp = save_str_temp(&structure, i, str_temp);

		// 	if (strcmp(str_temp, ))
		// 	printf("%s\n", str_temp);
			
		// 	// printf("%s\n", structure.envp_export[i]);
		// 	i++;
		// }
		
		get_path_env(&structure);
		while (1)
		{
			if (!parser(&structure, &prompt))
				continue ;
			else
				execution(&structure, &prompt);
		}
	}
	return (0);
}
