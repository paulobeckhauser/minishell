/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/13 18:56:09 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execution(int argc, char *argv[], char *envp[], t_info *structure)
{
	char **command;
	char *input;
	pid_t child_pid;
	char **possible_paths;

	store_main_arguments(argc, argv, envp, structure);
	get_path_env(structure);

	int i;
	char *home_dir;


	char *cur_path;
    char *buf;
    size_t size;

	while (1)
	{
		printf(ANSI_COLOR_GREEN "minishell> " ANSI_COLOR_RESET);
		input = readline("");

		// EXIT FUNCTION
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		// EXIT FUNCTION
		command = ft_split(input, ' ');
		check_builtin(structure, command[0]);

		// cur_path = getcwd(buf, size);
    	// printf("HERE!!!: %s\n", cur_path);
		

		if (structure->is_builtin)
		{
			// cd with only a relative or absolute path
			if (is_cd_command(command))
				execute_cd_command(command);
			if (is_pwd_command(command))
				execute_pwd_command(command);
			if (is_echo_command(command))
				execute_echo_command(command, 1); // need to implement reedirection
			if (is_export_command(command))
				execute_export_command(command);
			if (is_unset_command(command))
				execute_unset_command(command);
			if (is_env_command(command))
				execute_env_command(command);
			if (is_exit_command(command))
				execute_exit_command(command);
			

			
			

			continue;


			
		}

		else
		{
			
			structure->possible_paths = split_concat_command(structure->path_env,
					':', command[0]);

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
}