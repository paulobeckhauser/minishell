/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:11:20 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/12 00:46:06 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_primary_redirection_vars(t_token *token, t_prompt *prompt)
{
	token->in.fd = 0;
	token->in.file_name = NULL;
	token->in.heredoc = false;
	token->out.fd = 1;
	token->out.file_name = NULL;
	token->t_value.single_ptr = verify_redirection(prompt);
	token->last_redirection = false;
}

void	init_in_redirection(t_token *token, char *file_name)
{
	t_in	in;

	in.heredoc = false;
	in.fd = open(file_name, O_RDONLY);
	if (in.fd == -1)
		ft_printf("bash: %s: No such file or directory\n", file_name);
	else
		in.file_name = file_name;
	token->in = in;
	token->type = REDIRECTION;
}

void	init_heredoc_in_redirection(t_token *token, char *delimiter)
{
	t_in	in;
	pid_t	pid;

	g_signal = 1;
	create_tmp_folder();
	in.heredoc = true;
	in.file_name = "tmp/heredoc_tmp";
	in.fd = 0;
	pid = fork();
	if (pid == 0)
		run_heredoc(&in, token, delimiter);
	token->type = REDIRECTION;
	token->in = in;
	waitpid(pid, NULL, 0);
	g_signal = 0;
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
