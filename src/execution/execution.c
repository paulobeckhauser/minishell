/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:43:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/28 15:00:19 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execution(t_info *structure, t_prompt *prompt)
{



	pid_t child_pid;
	int i;


	

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
			execute_echo_command(structure->table->arr, 1, structure); // need to implement reedirection
		if (is_export_command(structure->table->arr))
			execute_export_command(structure);
		if (is_unset_command(structure->table->arr))
			execute_unset_command(structure);
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
				if (structure->table->in.file_name)
				{
					dup2(structure->table->in.fd, STDIN_FILENO);
					close(structure->table->in.fd);
				}
				else if (i != 0)
				{
					dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
					close(structure->fds_pipes[i - 1][0]);
				}
				
				if (structure->table->out.file_name)
				{
					dup2(structure->table->out.fd, STDOUT_FILENO);
					close(structure->table->out.fd);
				}

				else if (structure->table->next != NULL)
				{
					dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
					close(structure->fds_pipes[i][1]);
				}

		
				if (structure->table->type == BUILTIN_CMD)
				{
					if (is_cd_command(structure->table->arr))
						execute_cd_command(structure->table->arr); // cd with only a relative or absolute path
					if (is_pwd_command(structure->table->arr))
						execute_pwd_command(structure->table->arr);
					if (is_echo_command(structure->table->arr))
						execute_echo_command(structure->table->arr, 1, structure); // need to implement reedirection
					if (is_export_command(structure->table->arr))
						execute_export_command(structure);
					if (is_unset_command(structure->table->arr))
						execute_unset_command(structure);
					if (is_env_command(structure->table->arr))
						execute_env_command(structure->table->arr);
					if (is_exit_command(structure->table->arr))
						execute_exit_command(structure->table->arr);
					
					exit(0);
							
				}

		


				else
				{
					execve(structure->path_commands[i], structure->table->arr, structure->envp);
				}
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

		i = 0;
		while (i < structure->number_commands)
		{
			waitpid(structure->pid[i], NULL, 0);
			i++;
		}
	}

}
