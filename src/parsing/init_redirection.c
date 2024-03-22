/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:11:20 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/22 20:23:50 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_in	init_in_redirection(t_token *token, char *file_name)
{
	t_in	in;

	in.heredoc = false;
	if ((in.fd = open(file_name, O_RDONLY)) == -1)
	{
		file_name = ft_strjoin("bash: ", file_name);
		perror(file_name);
	}
	
		// perror(file_name);
	// if (in.fd == -1)
	// {
	// 	in.file_name = NULL;
	// 	ft_printf("bash: %s: No such file or directory\n", file_name);
	// }
	else
		in.file_name = file_name;
	token->in = in;
	token->type = REDIRECTION;
	return (in);
}

t_in	init_heredoc_in_redirection(t_token *token, char *file_name)
{
	t_in	in;

	in.heredoc = true;
	in.fd = -1;
	in.file_name = file_name;
	token->in = in;
	token->type = REDIRECTION;
	return (in);
}


t_out	init_truncate_out_redirection(t_token *token, char *file_name)
{
	t_out	out;

	out.fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	out.file_name = file_name;
	if (out.fd == -1)
	{
		ft_printf("bash: error creating file `%s'\n", out.file_name);
		token->type = END;
		return (out);
	}
	token->out = out;
	token->type = REDIRECTION;
	return (out);
}

t_out	init_append_out_redirection(t_token *token, char *file_name)
{
	t_out	out;

	out.fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	out.file_name = file_name;
	if (out.fd == -1)
	{
		ft_printf("bash: error creating file `%s'\n", out.file_name);
		token->type = END;
		return (out);
	}
	token->out = out;
	token->type = REDIRECTION;
	return (out);
}
