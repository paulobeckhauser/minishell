/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/10 15:06:29 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipes_implementation(t_info *structure)
{
    int	i;
    int	dev_null_fd;
    int command_number;
    pid_t w_id;

    create_pipes(structure);
    structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1),
            sizeof(pid_t));
    i = 0;
    dev_null_fd = open("/dev/null", O_RDONLY);

    command_number = 0;
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
            if (structure->table->in.file_name)
            {
                if (structure->table->in.heredoc)
                {
                    structure->table->in.fd = open("tmp/heredoc_tmp", O_RDONLY);
                    if (structure->table->in.fd == -1)
                    {
                        perror("open failed");
                        exit(EXIT_FAILURE);
                    }
                    
                }
                if (structure->table->in.fd != 0)
                {
                    dup2(structure->table->in.fd, STDIN_FILENO);
                    close(structure->table->in.fd);
                }
                else
                {
                    close(structure->table->in.fd);
                    dup2(dev_null_fd, STDIN_FILENO);
                    
                }
            }
            
            if (i != 0)
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
            else
            {
                if (execve(structure->path_commands[i], structure->table->arr,
                        structure->envp) == -1)
                {                   
                    structure->last_exit_status = EX_COMM_NOTFOUND;



                    if(command_number == structure->number_commands)
                    {
                        exit(EX_COMM_NOTFOUND);
                    }
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
    close(dev_null_fd);
    int status;
    
    w_id = wait_child_processes(structure, &status);

    if (status == 256)
        structure->last_exit_status = EX_FAILURE;
    
    else if (status == 32512)
        structure->last_exit_status = EX_COMM_NOTFOUND;

}
