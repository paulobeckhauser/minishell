/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_implementation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:07:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 20:20:17 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void pipes_implementation(t_info *structure)
{
	int i;
    
    create_pipes(structure);
    structure->pid = (pid_t *)ft_calloc((structure->number_commands + 1), sizeof(pid_t));
    i = 0;

    while(structure->table)
    {
        structure->pid[i] = fork();

        // printf("%d\n", i);

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
                builtin_execution(structure);				
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
