/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/18 20:56:43 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// cur_path = getcwd(buf, size);
// printf("HERE!!!: %s\n", cur_path);
// char *cur_path;
// char *buf;
// size_t size;

// char *user = getenv("USER")

void	execution(int argc, char *argv[], char *envp[], t_info *structure)
{
	pid_t child_pid;
	// char **possible_paths;

	int i;
	// int k;

	get_number_commands(structure);
	store_commands(structure);
	store_path_commands(structure);
	// // CREATE PIPES
	// structure->fds_pipes = (int **)ft_calloc((structure->number_commands), sizeof(int *));
	// if (structure->fds_pipes == NULL)
	// {
	// 	perror("Memory allocation failed");
	// 	return ;
	// }

	// i = 0;
	// while (i < structure->number_commands - 1)
	// {
	// 	structure->fds_pipes[i] = (int *)ft_calloc(2 + 1, sizeof(int));
	// 	if (structure->fds_pipes[i] == NULL)
	// 	{
	// 		perror("Memory allocation failed");
	// 		return ;
	// 	}
	// 	if (pipe(structure->fds_pipes[i]) == -1)
	// 		perror("Pipe creation failed");
	// 	i++;
	// }
	// structure->fds_pipes[i] = NULL;
	create_pipes(structure);


	structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1), sizeof(pid_t));
	i = 0;

	while(structure->table)
	{
		structure->pid[i] = fork();

		if (structure->pid[i] == 0)
		{
			if (i != 0)
			{
				dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
				close(structure->fds_pipes[i - 1][0]);
			}
			
			if (structure->table->next != NULL)
			{
				dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
				close(structure->fds_pipes[i][1]);
			}
			// Execute the command
        	execve(structure->path_commands[i], structure->table->arr, structure->envp);
		}

		else
		{
			if (i != 0)
				close(structure->fds_pipes[i - 1][0]);
			if (structure->table->next != NULL)
				close(structure->fds_pipes[i][1]);
		}

		i++;
		structure->table = structure->table->next;

	}

		// // WAIT CHILD PROCESSES
	i = 0;
	while (i < structure->number_commands)
	{
		waitpid(structure->pid[i], NULL, 0);
		i++;
	}
	// WAIT CHILD PROCESSES
















	

	//CREATE CHILD PROCESSES
	// create_child_processes(structure);
	// structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1),
	// 		sizeof(pid_t));
	// i = 0;
	// // while(i < structure->number_commands)
	// while(structure->table)
	// {
	// 	structure->pid[i] = fork();

	// 	if (structure->pid[i] == 0) // This is a child process
	// 	{
	// 		if (i != 0)
	// 		{
	// 			dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
	// 			close(structure->fds_pipes[i - 1][0]);
	// 		}
	// 		if (i != structure->number_commands - 1)
	// 		{
	// 			dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
	// 			close(structure->fds_pipes[i][1]);
	// 		}

	// 		// Close the unused ends of the pipes
	// 		if (i != 0)
	// 			close(structure->fds_pipes[i - 1][1]);
	// 		if (i != structure->number_commands - 1)
	// 			close(structure->fds_pipes[i][0]);
			
	// 		execve(structure->path_commands[i], structure->table->arr, structure->envp);
	// 		exit(0);//ensure the child process ends after execve
	// 	}
	// 	else // This is the parent process
	// 	{
	// 		if (i != 0)
	// 			close(structure->fds_pipes[i - 1][1]);
	// 		if (i != structure->number_commands - 1)
	// 			close(structure->fds_pipes[i][0]);
	// 	}


		
	
	// 	structure->table = structure->table->next;
	// 	i++;



		
	// }	
	// // WAIT CHILD PROCESSES
	// i = 0;
	// while (i < structure->number_commands)
	// {
	// 	waitpid(structure->pid[i], NULL, 0);
	// 	i++;
	// }
	// WAIT CHILD PROCESSES

		

	// //


	// allocate_memory_commands
	// i = 0;

	
	
	
	// allocate_memory_commands



	// Allocate memory path
	// i = 0;
    // structure->path_commands = (char **)malloc((structure->number_commands + 1) * sizeof(char *));
    // if (!structure->path_commands)
    // {
    //     perror("Memory allocation failed!\n");
    //     exit(EXIT_FAILURE);
    // }
	// Allocate memory path

	
	// i = 0;
	// while(i < structure->number_commands)
	// {
	// 	structure->possible_paths = split_concat_command(structure->path_env,
	// 			':', structure->table->arr[i]);
	// }


	
	
	// while (structure->table)
	// {
		
	// 	printf("%s\n", structure->table->arr[0]);
	// 	structure->table = structure->table->next;
	// }
	


	// Allocate memory path
	// i = 0;
    // structure->path_commands = (char **)malloc((structure->number_commands + 1) * sizeof(char *));
    // if (!structure->path_commands)
    // {
    //     perror("Memory allocation failed!\n");
    //     exit(EXIT_FAILURE);
    // }
	// Allocate memory path

	// while (structure->table)
	// {
		
	// 	printf("%s\n", structure->table->arr[0]);
	// 	structure->table = structure->table->next;
	// }




	

	// printf("%d\n", structure->number_commands);

	

	// while (structure->table)
	// {
		
		
	// 	structure->table = structure->table->next;
	// }

	

	// store_path_commands(structure);

	// int i;
	// int j;

	








	// CREATE PIPES
	// structure->fds_pipes = (int **)ft_calloc((structure->number_commands), sizeof(int *));
	// if (structure->fds_pipes == NULL)
	// {
	// 	perror("Memory allocation failed");
	// 	return ;
	// }

	// i = 0;

	// while(i < structure->number_commands - 1)
	// {
	// 	structure->fds_pipes[i] = (int *)ft_calloc(2 + 1, sizeof(int));
	// 	if (structure->fds_pipes[i] == NULL)
	// 	{
	// 		perror("Memory allocation failed");
	// 		// free_variables(structure);
	// 		return ;
	// 	}
	// 	if (pipe(structure->fds_pipes[i]) == -1)
	// 		perror("Pipe creation failed");
	// 	i++;
	// }
	// structure->fds_pipes[i] = NULL;



	
	
	// printf("%d\n", structure->number_commands);
	// int number_commands;

	// number_commands = 0;
	// while(structure->table)
	// {
	// 	if (structure->table->arr[0])
	// 	{
	// 		number_commands++;
	// 		printf("%s\n", structure->table->arr[0]);
	// 	}
	// 	structure->table = structure->table->next;
	// }
	

	// structure->number_commands = number_commands;

	




	// while(structure->table)
	// {
	// 	if (structure->table->type == BUILTIN_CMD)
	// 	{
	// 		if (is_cd_command(structure->table->arr))
	// 			execute_cd_command(structure->table->arr); // cd with only a relative or absolute path
	// 		if (is_pwd_command(structure->table->arr))
	// 			execute_pwd_command(structure->table->arr);
	// 		if (is_echo_command(structure->table->arr))
	// 			execute_echo_command(structure->table->arr, 1); // need to implement reedirection
	// 		if (is_export_command(structure->table->arr))
	// 			execute_export_command(structure->table->arr, envp);
	// 		if (is_unset_command(structure->table->arr))
	// 			execute_unset_command(structure->table->arr);
	// 		if (is_env_command(structure->table->arr))
	// 			execute_env_command(structure->table->arr);
	// 		if (is_exit_command(structure->table->arr))
	// 			execute_exit_command(structure->table->arr);
	// 	}
	// 	else
	// 	{
			


			
	// 		structure->possible_paths = split_concat_command(structure->path_env,
	// 				':', structure->table->arr[0]);

	// 		i = 0;
	// 		while (structure->possible_paths[i])
	// 		{
	// 			if (access(structure->possible_paths[i], X_OK) == 0)
	// 				break ;

	// 			i++;
	// 		}
	// 		if (!structure->possible_paths[i])
	// 			i--;
	// 		structure->path_command = ft_strdup(structure->possible_paths[i]);
	// 		free_2d_array(structure->possible_paths);

	// 		child_pid = fork();
	// 		if (child_pid < 0)
	// 		{
	// 			perror("Fork failed");
	// 			exit(1);
	// 		}

	// 		if (child_pid == 0)
	// 		{
	// 			if (execve(structure->path_command, structure->table->arr,
	// 					envp) < 0)
	// 			{
	// 				perror(structure->table->arr[0]);
	// 				exit(1);
	// 			}
	// 			printf("This won't be printed if execvp is successful\n");
	// 		}
	// 		else
	// 			waitpid(child_pid, NULL, 0);
	// 	}
			

	// 	structure->table = structure->table->next;
	// }

}