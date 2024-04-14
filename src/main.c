/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:10:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/14 12:01:41 by pabeckha         ###   ########.fr       */
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

	char **test_arr;
	int i;

	if (argc == 1)
	{
		(void)argv;
		
		init_vars(&structure);
		store_envp(envp, &structure);

		prompt.folder = NULL;

		structure.folder = NULL;
		structure.folder_deleted = 0;

		char *str;
		
		while (1)
		{
			
			test = getcwd(cwd, sizeof(cwd));
			// structure.folder = getcwd(cwd, sizeof(cwd));
			// printf("\nThe value of current path is: %s\n\n", test);
			// printf("\nThe value of previous path is: %s\n", prompt.folder);
			// printf("\nThe value of previous path is: %s\n", structure.folder);

			// if (structure.folder != NULL)
			// {
				
			// 	test_arr = ft_split(structure.folder, '/');
			// 	// printf("here\n");

			// 	i = 0;

			// 	while (test_arr[i])
			// 	{
			// 		i++;
			// 	}
			// 	// printf("The last path is: %s\n", test_arr[i - 1]);
			// 	free_2d_array(test_arr);
			// }

			if (test == NULL)
			{
				// printf("here\n");
				str = ft_strdup(structure.folder);
				// printf("here 2\n");
				// printf("HAAAA HERE IS THE NEW STRING %s\n", str);
				// free(structure.folder);
				// printf("here 3\n");
				structure.folder = get_parent_folder(str);
				// printf("here 4\n");
				printf("%s\n", structure.folder);

				// int m = 0;

				// while (str[m])
				// {
				// 	ft_putchar_fd(str[m], 1);
				// 	m++;
				// }
				// ft_putchar_fd('\n', 1);
				

				

			}

			

			
			
			

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
