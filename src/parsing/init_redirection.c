/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:11:20 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/28 17:07:22 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_in	init_in_redirection(t_token *token, char *file_name)
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
	return (in);
}

t_in	init_heredoc_in_redirection(t_token *token, char *file_name)
{
	t_in	in;
	char	*delimiter;

	in.heredoc = true;
	delimiter = readline("> ");
	in.heredoc_in = NULL;
	while (ft_strcmp(delimiter, file_name) != 0)
	{
		if (!in.heredoc_in)
			in.heredoc_in = "";
		else
			in.heredoc_in = ft_strjoin(in.heredoc_in, "\n");
		in.heredoc_in = ft_strjoin(in.heredoc_in, delimiter);
		delimiter = readline("> ");
	}
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
