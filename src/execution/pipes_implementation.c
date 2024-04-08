/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/08 19:59:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipes_implementation(t_info *structure)
{
    int	i;
    int	dev_null_fd;

    create_pipes(structure);
    structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1),
            sizeof(pid_t));
    i = 0;
    dev_null_fd = open("/dev/null", O_RDONLY);
    int command_number;

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
                close(structure->fds_pipes[i - 1][0]); // Close read end of the pipe in the child
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
            if (structure->table->type == BUILTIN_CMD)
                builtin_execution(structure);
            else
            {
				int j = 0;
				while (j < structure->number_commands - 1)
				{
				    close(structure->fds_pipes[j][0]);
				    close(structure->fds_pipes[j][1]);
				    j++;
				}
                if (execve(structure->path_commands[i], structure->table->arr,
                        structure->envp) == -1)
                {
                    ft_putstr_fd(structure->commands[i], 2);
                    ft_putstr_fd(": command not found\n", 2);
                    
                    if(command_number == structure->number_commands)
                    {
                        // printf("The number of commands is: %d\n", structure->number_commands);
                        // printf("The number of commands is: %d\n", structure->number_commands);
                        exit(127);
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
    wait_child_processes(structure);
}
