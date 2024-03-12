/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/12 18:34:56 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	main(int argc, char *argv[], char *envp[])
void execution(int argc, char *argv[], char *envp[], t_info *structure)
{
	char **command;
	char *input;
	pid_t child_pid;
	char **possible_paths;

	store_main_arguments(argc, argv, envp, structure);
	get_path_env(structure);

	int i;

	while (1)
	{
        printf(ANSI_COLOR_GREEN "minishell> " ANSI_COLOR_RESET);
		input = readline("");
		
		// EXIT FUNCTION
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		// EXIT FUNCTION
		command = ft_split(input, ' ');
		check_builtin(structure, command[0]);



		if (ft_strcmp(command[0], "cd") == 0)
		{
			// printf("cd function\n");

			printf("%s\n", command[0]);
			printf("%s\n", command[1]);
			
			char *function;
			char *buff_curdir;
			size_t sizet_curdir;

			function = getcwd(buff_curdir, sizet_curdir);

			


			

			
			
			
			
			

			

			printf("Return: %s\n", function);
			// printf("Buffer: %s\n", buf);
			// printf("Size: %zu\n", size);


			
			// chdir(command[1]);

			// if (cd(command[1]) < 0)
			// 	perror(command[1]);

			
	
			continue;
		
		}


		structure->possible_paths = split_concat_command(structure->path_env, ':',
				command[0]);

		i = 0;
		while (structure->possible_paths[i])
		{
			if (access(structure->possible_paths[i], X_OK) == 0)
				break ;

			i++;
		}
		if (!structure->possible_paths[i])
			i--;
        structure->path_command = ft_strdup(structure->possible_paths[i]);
		free_2d_array(structure->possible_paths);

		child_pid = fork();
		if (child_pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}

		if (child_pid == 0)
		{
			if (execve(structure->path_command, command, envp) < 0)
			{
				perror(command[0]);
				exit(1);
			}
			printf("This won't be printed if execvp is successful\n");
		}

		else
			waitpid(child_pid, NULL, 0);

		free(input);
		free(command);
	}


}