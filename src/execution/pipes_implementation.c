/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 22:19:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipes_implementation(t_info *structure)
{
    int	i;
    int command_number;
    pid_t w_id;
	t_cmd	*head;

    create_pipes(structure);
    structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1),
            sizeof(pid_t));
    i = 0;
    
    char **current;
    bool    redirection = false;

    current = structure->table->arr;
    if (structure->table->in.file_name)
        redirection = true;

    command_number = 0;
	head = structure->table;
    while (structure->table)
    {
        command_number++;
		handle_child_key_combos();
        structure->pid[i] = fork();
        if (structure->pid[i] == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (structure->pid[i] == 0)
        {
			if (!open_files(structure->table))
				exit(EXIT_FAILURE);
			if (structure->table->in.fd == 0)
			{
				// if (THERE IS OUT REDIRECT)
				// {
				// 	do not dup into pipe, because its duplicated to fd
				// }
				// else
				// 	do it 

				if (structure->table->out.fd == 0)
				{
					if (i != 0)
					{
						close(structure->fds_pipes[i - 1][1]);
						dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
					}

					if (structure->table->next != NULL)
					{
						close(structure->fds_pipes[i][0]);
						dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
					}
				}

				else
				{
					if (i != 0)
					{
						close(structure->fds_pipes[i - 1][1]);
						dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
					}

				}
			}
			else if (structure->table->in.fd > 0)
			{
				if (structure->table->out.fd == 0)
				{
					if (i != 0)
					{
						dup2(structure->fds_pipes[i - 1][1], STDIN_FILENO);
						close(structure->fds_pipes[i - 1][0]);
					}
					
					
					if (structure->table->next != NULL)
					{
						dup2(structure->fds_pipes[i][1], STDOUT_FILENO);
						close(structure->fds_pipes[i][1]);
					}
				}
				else
				{
					if (i != 0)
					{
						close(structure->fds_pipes[i - 1][1]);
						dup2(structure->fds_pipes[i - 1][0], STDIN_FILENO);
					}
				}
				// if (THERE IS OUT REDIRECT)
				// {
				// 	do not dup into pipe, because its duplicated to fd
				// }
				// else
				// 	do it
				// else
				// {
					
				// }
			}

            int j = 0;
            while (j < structure->number_commands - 1)
            {
                close(structure->fds_pipes[j][0]);
                close(structure->fds_pipes[j][1]);
                j++;
            }
            if (structure->table->type == BUILTIN_CMD)
            {
				builtin_execution(structure);
                exit(EXIT_SUCCESS);
                
            }
			
            {
                if (execve(structure->path_commands[i], structure->table->arr,
                        structure->envp) == -1)
                {             
                		check_path(structure->path_commands[i], structure->table->arr[0]);
						// structure->last_exit_status = EX_COMM_NOTFOUND;

						// if(command_number == structure->number_commands)
						// {
						// 	exit(EX_COMM_NOTFOUND);
						// }
						
                }
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

    structure->table = head;    
    int status;
    
    w_id = wait_child_processes(structure, &status);
	free_2d_int_array(structure->fds_pipes);
	free_2d_array(structure->commands);
	free_2d_array(structure->path_commands);
	free(structure->path_env);
	free(structure->pid);
}

