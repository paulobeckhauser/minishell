/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:32 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/16 20:49:25 by pabeckha         ###   ########.fr       */
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
	t_cmd	*table;

	store_main_arguments(argc, argv, envp, &structure);
	get_path_env(&structure);
	while (1)
	{ 
		parser(&table);
		structure.table = table;
		execution(argc, argv, envp, &structure);
	}
	return (0);
}
