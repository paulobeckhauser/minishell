/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:32 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/04 19:48:41 by sfrankie         ###   ########.fr       */
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

int	main(void)
{
    char	*buf;
    char	*input;

    while (1)
    {
		// display_dir_prompt_history (code below will be stored in the function)
		buf = getcwd(NULL, 0);
        if (buf == NULL)
		{
            perror("getcwd() error");
            return (1);
        }
		buf = ft_strjoin(buf, "$ ");
        input = readline(buf);
        add_history(input);
		free(input);
        free(buf);
    }
    return (0);
}
