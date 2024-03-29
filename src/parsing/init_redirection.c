/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:11:20 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/29 19:37:07 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_in_redirection(t_token *token, char *file_name)
{
	t_in	in;

	in.heredoc = false;
	in.heredoc_in = NULL;
	if ((in.fd = open(file_name, O_RDONLY)) == -1)
	{
		file_name = ft_strjoin("bash: ", file_name);
		perror(file_name);
	}
	else
		in.file_name = file_name;
	token->in = in;
	token->type = REDIRECTION;
}

void	init_heredoc_in_redirection(t_token *token, char *delimiter)
{
	t_in	in;
	char	*heredoc_newline;
	char	*heredoc_msg;

	create_tmp_folder();
	in.heredoc = true;
	in.file_name = "tmp/heredoc_tmp";
	heredoc_newline = readline("> ");
	heredoc_msg = NULL;
	while (ft_strcmp(heredoc_newline, delimiter) != 0)
	{
		if (!heredoc_msg)
			heredoc_msg = "";
		else
			heredoc_msg = ft_strjoin(heredoc_msg, "\n");
		heredoc_msg = ft_strjoin(heredoc_msg, heredoc_newline);
		free(heredoc_newline);
		heredoc_newline = readline("> ");
	}
	free(heredoc_newline);
	in.fd = open(in.file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (in.fd == -1)
	{
		perror("open");
		return ;
	}
	if (heredoc_msg)
	{
		if (write(in.fd, heredoc_msg, ft_strlen(heredoc_msg)) == -1)
		{
			perror("write");
			return ;
		}
	}
	token->in = in;
	token->type = REDIRECTION;
}

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
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
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

void	init_truncate_out_redirection(t_token *token, char *file_name)
{
	t_out	out;

	out.fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	out.file_name = file_name;
	if (out.fd == -1)
	{
		ft_printf("bash: error creating file `%s'\n", out.file_name);
		token->type = END;
		return ;
	}
	token->out = out;
	token->type = REDIRECTION;
}

void	init_append_out_redirection(t_token *token, char *file_name)
{
	t_out	out;

	out.fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	out.file_name = file_name;
	if (out.fd == -1)
	{
		ft_printf("bash: error creating file `%s'\n", out.file_name);
		token->type = END;
		return ;
	}
	token->out = out;
	token->type = REDIRECTION;
}
