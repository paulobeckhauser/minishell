/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:12:51 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/12 00:40:31 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	create_tmp_folder(void)
{
	char	**create_tmp_folder;
	pid_t	pid;

	create_tmp_folder = malloc(4 * sizeof(char *));
	if (!create_tmp_folder)
		return ;
	create_tmp_folder[0] = "/bin/mkdir";
	create_tmp_folder[1] = "-p";
	create_tmp_folder[2] = "tmp";
	create_tmp_folder[3] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (execve(create_tmp_folder[0], create_tmp_folder, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
	free(create_tmp_folder);
}

void	run_heredoc(t_in *in, t_token *token, char *delimiter)
{
	char	*heredoc_newline;
	char	*heredoc_msg;

	handle_heredoc_combos();
	wait_for_heredoc_delimiter(&heredoc_newline, &heredoc_msg, delimiter);
	open_write_close_tmp_file(token, in, &heredoc_msg);
	exit(0);
}

void	wait_for_heredoc_delimiter(char **heredoc_newline, char **heredoc_msg,
	char *delimiter)
{
	*heredoc_newline = readline("> ");
	if (*heredoc_newline == NULL)
	{
		ft_printf("bash: warning: here-document delimited by end-of-file");
		ft_printf(" (wanted `stop')\n");
		exit(0);
	}
	*heredoc_msg = "";
	while (ft_strcmp(*heredoc_newline, delimiter) != 0)
	{
		*heredoc_msg = ft_strjoin(*heredoc_msg, *heredoc_newline);
		*heredoc_msg = ft_strjoin(*heredoc_msg, "\n");
		free(*heredoc_newline);
		*heredoc_newline = readline("> ");
		if (*heredoc_newline == NULL)
		{
			ft_printf("bash: warning: here-document delimited by ");
			ft_printf("end-of-file (wanted `stop')\n");
			exit(EXIT_SUCCESS);
		}
	}
	free(*heredoc_newline);
}

void	open_write_close_tmp_file(t_token *token, t_in *in, char **heredoc_msg)
{
	in->fd = open(in->file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (in->fd == -1)
	{
		perror("open");
		return ;
	}
	if (*heredoc_msg)
	{
		if (write(in->fd, *heredoc_msg, ft_strlen(*heredoc_msg)) == -1)
		{
			perror("write");
			return ;
		}
	}
	if (close(in->fd) == -1)
	{
		perror("close");
		return ;
	}
}
