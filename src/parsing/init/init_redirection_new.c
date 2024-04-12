/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:12:35 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/13 00:27:54 by sfrankie         ###   ########.fr       */
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
	pid_t	pid;

	g_signal = 1;
	create_tmp_folder();
	token->in.heredoc = true;
	token->in.file_name[0] = "tmp/heredoc_tmp";
	token->in.file_name[1] = NULL;
	token->in.fd = 0;
	pid = fork();
	if (pid == 0)
		run_heredoc(token, delimiter);
	token->type = REDIRECTION;;
	waitpid(pid, NULL, 0);
	g_signal = 0;
}

void	init_truncate_out_redirection(t_token *token, char *file_name)
{
	token->out.file_name[0] = file_name;
	token->out.file_name[1] = NULL;
	token->out.fd = 0;
	token->out.trunc = true;
	token->type = REDIRECTION;
}

void	init_append_out_redirection(t_token *token, char *file_name)
{
	token->out.file_name[0] = file_name;
	token->out.file_name[1] = NULL;
	token->out.fd = 0;
	token->out.trunc = false;
	token->type = REDIRECTION;
}
