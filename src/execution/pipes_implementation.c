/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 14:52:51 by sfrankie         ###   ########.fr       */
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
			else
				
			if (structure->table->in.fd == 0)
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
			else if (structure->table->in.fd > 0)
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
	
	// printf("%d\n", status);


    // if (status == 256)
    //     structure->last_exit_status = 1;
    
    // else if (status == 32512)
    //     structure->last_exit_status = 127;

    // else if (status == 512)
    // {
    //     if (ft_strcmp(current[0], "grep") == 0 && !current[2] && redirection)
    //         structure->last_exit_status = 1;
    //     else
    //         structure->last_exit_status = 2;
    // }
    
    // else if (status == 0)
    //     structure->last_exit_status = 0;


}

