/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:32 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/11 15:26:18 by pabeckha         ###   ########.fr       */
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


#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "../../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char **command;
	char *input;
	pid_t child_pid;
	char **possible_paths;

	t_info structure;

	structure.envp = envp;

	get_path_env(&structure);

	int g;

	while (1)
	{
        printf(ANSI_COLOR_GREEN "minishell> " ANSI_COLOR_RESET);
		input = readline("");
		
		// EXIT FUNCTION
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		// EXIT FUNCTION
		command = ft_split(input, ' ');

        
		check_builtin(&structure, command[0]);
        
		// if (strcmp(command[0], "cd") == 0)
		// {
		// 	if (cd(command[1]) < 0)
		// 	{
		// 		perror(command[1]);
		// 	}
		// 	continue ;
		// }


		structure.possible_paths = split_concat_command(structure.path_env, ':',
				command[0]);

		g = 0;
		while (structure.possible_paths[g])
		{
			if (access(structure.possible_paths[g], X_OK) == 0)
				break ;

			g++;
		}
		if (!structure.possible_paths[g])
			g--;
        structure.path_command = ft_strdup(structure.possible_paths[g]);
		free_2d_array(structure.possible_paths);

		child_pid = fork();
		if (child_pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}

		if (child_pid == 0)
		{
			if (execve(structure.path_command, command, envp) < 0)
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
