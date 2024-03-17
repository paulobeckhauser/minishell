/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/16 19:52:46 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execution(int argc, char *argv[], char *envp[], t_info *structure)
{
	char **command;
	char *input;
	pid_t child_pid;
	char **possible_paths;



	int i;
	char *home_dir;


	// char *cur_path;
    // char *buf;
    // size_t size;

	// char *user = getenv("USER")



	if (structure->table->type == BUILTIN_CMD)
	

	// cur_path = getcwd(buf, size);
	// printf("HERE!!!: %s\n", cur_path);
	
	// while(structure->table)
	// {
	// 	// CREATION OF PIPES
		
	// }

	// if (structure->is_builtin)
	{
		// cd with only a relative or absolute path
		if (is_cd_command(structure->table->arr))
			execute_cd_command(structure->table->arr);
		if (is_pwd_command(structure->table->arr))
			execute_pwd_command(structure->table->arr);
		if (is_echo_command(structure->table->arr))
			execute_echo_command(structure->table->arr, 1); // need to implement reedirection
		if (is_export_command(structure->table->arr))
			execute_export_command(structure->table->arr, envp);
		if (is_unset_command(structure->table->arr))
			execute_unset_command(structure->table->arr);
		if (is_env_command(structure->table->arr))
			execute_env_command(structure->table->arr);
		if (is_exit_command(structure->table->arr))
			execute_exit_command(structure->table->arr);

		// continue;


		
	}

	else
	{

		
		
		// printf("%s\n", structure->table->arr[4]);
		structure->possible_paths = split_concat_command(structure->path_env,
				':', structure->table->arr[0]);

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
			if (execve(structure->path_command, structure->table->arr, envp) < 0)
			{
				perror(command[0]);
				exit(1);
			}
			printf("This won't be printed if execvp is successful\n");
		}

		else
			waitpid(child_pid, NULL, 0);

	// free(input);
	// free(command);

	
	}
	
		
		

	
	// }
}