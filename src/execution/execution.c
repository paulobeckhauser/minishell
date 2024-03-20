/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/19 18:43:34 by pabeckha         ###   ########.fr       */
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
	if (structure->table->type == BUILTIN_CMD && structure->number_commands == 1)
	{
		if (is_cd_command(structure->table->arr))
			execute_cd_command(structure->table->arr); // cd with only a relative or absolute path
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
	}
	else
	{
		create_pipes(structure);
		structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1), sizeof(pid_t));
		i = 0;

		while(structure->table)
		{
			structure->pid[i] = fork();

			if (structure->pid[i] == 0)
			{ 
				// if (structure->table->redirection)
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


				// HANDLE REDIRECTIONS
				// -> Pseudocode
				// if (structure->table->redirection)
				// {
				// 	int fd;
					
				// 	if (structure->table->redirection_type == REDIRECT_OUT)
				// 	{
				// 		int fd_out
				// 		fd_out = open(structure->table->redirection_file, O_WRONLY | O_CREAT, 0644);
				// 		dup2(fd_out, STDOUT_FILENO);
						// close(fd_out) // Close the file descriptor after it's duplicated
				// 	}
				// 	if (structure->table->redirection_type == REDIRECT_IN)
				// 	{
				// 		int fd_in = open(structure->table->redirection_file, O_RDONLY);
				// 		dup2(fd_in, STDIN_FILENO);
				// 		close(fd_in); // Close the file descriptor after it's duplicated
				// 	}
				// }

				// HANDLE REDIRECTIONS


				
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
	}

}
