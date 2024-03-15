/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:32 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/15 14:35:56 by pabeckha         ###   ########.fr       */
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

#include "../inc/minishell.h"




int ft_setenv(const char *name, const char *value, int overwrite)
{
	size_t len;
	char *str;
	int result;
	
	if (!overwrite && getenv(name))
	{
		// The environment variable already exists and we don't want to overwrite it
		return (0);
	}

	// Calculate the length of the string we need to allocate
	len = ft_strlen(name) + ft_strlen(value) + 2; // +2 for the '=' and the null terminator
	
	// Allocate the string
	str = malloc(len);
	if (!str)
		return (-1);
	
	


	ft_strlcpy(str, name, ft_strlen(name) + 2);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	ft_strlcat(str, value, ft_strlen(value) + ft_strlen(str) + 1);

	result = putenv(str);

	// printf("%s\n", str);
	
	return (result);
	
}


int	main(int argc, char **argv, char **envp)
{
	// PAULO DATA STRUCTURE
	t_info structure;
	// PAULO DATA STRUCTURE
	

	// SZYMON DATA STRUCTURE
	// t_input_data	input_data;
	// SZYMON DATA STRUCTURE


	// while (1)
	// {
	// 	lexer(&input_data);
	// }


	// int i = 0;

	// while (envp[i])
	// {
	// 	// printf("%s\n", envp[i]);
	// 	i++;
	// }
	// envp[i] = "test=aaa";
	// envp[i + 1]= NULL;


	// i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	



	// if (argc == 1)
	// 	execution(argc, argv, envp, &structure);
	// else
	// 	printf("Incorrect number of arguments\n");


	int test;
	char *name;
	char *value;
	int overwrite;
	char *check;

	name = "TEST";
	value = "legal";
	overwrite = 1;

	// test = setenv(name, value, overwrite);

	// printf("%d\n", test);




	ft_setenv(name, value, overwrite);

	
	check = getenv(name);
	printf("%s\n", check);

	




	
	return (0);
}
