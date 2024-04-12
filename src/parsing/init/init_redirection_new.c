/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:12:35 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/12 21:50:10 by sfrankie         ###   ########.fr       */
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
	token->in.heredoc = false;
	token->in.file_name = ft_calloc(2, sizeof(char *));
	token->in.file_name[0] = malloc(ft_strlen(file_name) + 1);
	ft_strlcpy(token->in.file_name[0], file_name, ft_strlen(file_name) + 1);
	token->in.file_name[1] = NULL;
	token->type = REDIRECTION;
}

void	init_heredoc_in_redirection(t_token *token, char *delimiter)
{
	t_in	in;
	pid_t	pid;

	g_signal = 1;
	create_tmp_folder();
	in.heredoc = true;
	in.file_name[0] = "tmp/heredoc_tmp";
	in.file_name[1] = NULL;
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

	out.file_name[0] = file_name;
	out.file_name[1] = NULL;
	out.trunc = true;
	token->out = out;
	token->type = REDIRECTION;
}

void	init_append_out_redirection(t_token *token, char *file_name)
{
	t_out	out;

	out.file_name[0] = file_name;
	out.file_name[1] = NULL;
	out.trunc = false;
	token->out = out;
	token->type = REDIRECTION;
}
