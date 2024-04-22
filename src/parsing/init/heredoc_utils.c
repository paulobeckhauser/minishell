/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:12:51 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/22 09:58:54 by sfrankie         ###   ########.fr       */
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
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	free(create_tmp_folder);
}

void	run_heredoc(t_token *token, char *delimiter)
{
	char	*heredoc_newline;
	char	*heredoc_msg;

	wait_for_heredoc_delimiter(&heredoc_newline, &heredoc_msg, delimiter);
	open_write_close_tmp_file(token, &heredoc_msg);
	exit(0);
}

void	wait_for_heredoc_delimiter(char **heredoc_newline, char **heredoc_msg,
	char *delimiter)
{
	char	*tmp;

	tmp = NULL;
	handle_heredoc_key_combos();
	*heredoc_newline = readline("> ");
	if (*heredoc_newline == NULL)
	{
		ft_putstr_fd("bash: warning: here-document delimited by end-of-file", 1);
		ft_putstr_fd(" (wanted `", 1);
		ft_putstr_fd(delimiter, 1);
		ft_putstr_fd("')\n", 1);
		exit(EXIT_SUCCESS);
	}
	*heredoc_msg = ft_calloc(1, 1);
	while (ft_strcmp(*heredoc_newline, delimiter) != 0)
	{
		*heredoc_msg = strjoin_free_both(*heredoc_msg, *heredoc_newline);
		*heredoc_msg = strjoin_free_s1(*heredoc_msg, "\n");
		*heredoc_newline = readline("> ");
		if (*heredoc_newline == NULL)
		{
			ft_putstr_fd("bash: warning: here-document delimited by end-of-file", 1);
			ft_putstr_fd(" (wanted `", 1);
			ft_putstr_fd(delimiter, 1);
			ft_putstr_fd("')\n", 1);
			exit(EXIT_SUCCESS);
		}
	}
	free(*heredoc_newline);
}

void	open_write_close_tmp_file(t_token *token, char **heredoc_msg)
{
	token->in.fd = open("tmp/heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (token->in.fd == -1)
	{
		perror("open");
		return ;
	}
	if (*heredoc_msg)
	{
		if (write(token->in.fd, *heredoc_msg, ft_strlen(*heredoc_msg)) == -1)
		{
			perror("write");
			return ;
		}
	}
	if (close(token->in.fd) == -1)
	{
		perror("close");
		return ;
	}
	free(*heredoc_msg);
}
