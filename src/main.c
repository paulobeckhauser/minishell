/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:32 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/16 18:36:46 by sfrankie         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_info	structure;

	// PAULO DATA STRUCTURE
	// PAULO DATA STRUCTURE
	// SZYMON DATA STRUCTURE
	// t_input_data	input_data;
	// SZYMON DATA STRUCTURE
	// while (1)
	// {
	// 	lexer(&input_data);
	// }
	if (argc == 1)
		execution(argc, argv, envp, &structure);
	else
		printf("Incorrect number of arguments\n");
	// t_info structure; // PAULO DATA STRUCTURE
	t_cmd	table;

	while (1)
	{ 
		parser(&table);
	}
	return (0);
}
