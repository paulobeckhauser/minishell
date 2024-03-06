/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:32 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/06 18:54:27 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs


# include "../inc/minishell.h"



char **get_input(char *input)
{
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL)
    {
        perror("malloc failed");
        exit(1);
    }
    
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);

    while(parsed != NULL)
    {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;

    return(command);

    
    
}



int cd(char *path)
{
    return (chdir(path));
}



// int pwd(char *buf, size_t size)
// {
//     return (getcwd(buf, size));
// }





int	main(int argc, char *argv[], char *envp[])
{
    
    char **command;
    char *input;

    pid_t child_pid;

    while(1)
    {
        input = readline("minishell> ");
        command = get_input(input);



        // if (strcmp(command[0], "cd") == 0)
        // {
        //     if (cd (command[1]) < 0)
        //     {
        //         perror(command[1]);
        //     }
        //     continue;
        // }


        // if (strcmp(command[0], "pwd") == 0)
        // {
        //     if (pwd(command[1]) < 0)
        //     {
        //         perror(command[1]);
        //     }
        //     continue;
        // }






        
        
        child_pid = fork();
        if (child_pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }


        if (child_pid == 0)
        {
            // never returns if the call is successfull
            // execve(command[0], command, envp);
            if (execvp(command[0], command) < 0)
            // execve()
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


    
    return (0);
}