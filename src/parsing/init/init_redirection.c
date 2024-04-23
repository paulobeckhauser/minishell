/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:12:35 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 20:13:48 by sfrankie         ###   ########.fr       */
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
	token->out.trunc = NULL;
	token->val = verify_redirection(prompt);
	token->last_redirection = false;
}

void	init_in_redirection(t_token *token, char *file_name, t_prompt *prompt)
{
	if (!prompt->in_prio && !prompt->out_prio)
		prompt->in_prio = true;
	token->in.heredoc = false;
	token->in.file_name = ft_calloc(2, sizeof(char *));
	if (!token->in.file_name)
		return ;
	token->in.file_name[0] = file_name;
	token->in.file_name[1] = NULL;
	token->type = REDIRECTION;
}

void	init_heredoc_in_redirection(t_token *token, char *delimiter)
{
	pid_t	pid;

	create_tmp_folder();
	token->in.heredoc = true;
	token->in.file_name = ft_calloc(2, sizeof(char *));
	token->in.file_name[0] = ft_strdup("tmp/heredoc_tmp");
	token->in.file_name[1] = NULL;
	token->in.fd = 0;
	kill(0, SIGUSR1);
	g_signal = SIGUSR1;
	pid = fork();
	if (pid == 0)
		run_heredoc(token, delimiter);
	token->type = REDIRECTION;
	waitpid(pid, NULL, 0);
	g_signal = 0;
	free(delimiter);
}

void	init_truncate_out_redirection(t_token *token, char *file_name,
	t_prompt *prompt)
{
	if (!prompt->in_prio && !prompt->out_prio)
		prompt->out_prio = true;
	token->out.file_name = ft_calloc(2, sizeof(char *));
	if (!token->out.file_name)
		return ;
	token->out.file_name[0] = file_name;
	token->out.file_name[1] = NULL;
	token->out.fd = 0;
	token->out.trunc = ft_calloc(1, sizeof(int));
	if (!token->out.trunc)
		return ;
	token->out.trunc[0] = 1;
	token->type = REDIRECTION;
}

void	init_append_out_redirection(t_token *token, char *file_name,
	t_prompt *prompt)
{
	if (!prompt->in_prio && !prompt->out_prio)
		prompt->out_prio = true;
	token->out.file_name = ft_calloc(2, sizeof(char *));
	if (!token->out.file_name)
		return ;
	token->out.file_name[0] = file_name;
	token->out.file_name[1] = NULL;
	token->out.fd = 0;
	token->out.trunc = ft_calloc(1, sizeof(int));
	if (!token->out.trunc)
		return ;
	token->type = REDIRECTION;
}
