/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:57:30 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/15 14:29:35 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_files(t_cmd *table)
{
	if (table->in_prio)
	{
		if (!open_in_files(table) || !open_out_files(table))
			return (0);
	}
	else
	{
		if (!open_out_files(table) || !open_in_files(table))
			return (0);
	}
	return (1);
}

int	open_in_files(t_cmd *table)
{
	int	i;

	if (table->in.file_name)
	{
		i = 0;
		while (table->in.file_name[i + 1])
		{
			table->in.fd = open(table->in.file_name[i], O_RDONLY);
			if (table->in.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->in.file_name[i]);
				return (0);
			}
			if (close(table->in.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->in.file_name[i]);
				return (0);
			}
			i++;
		}
		if (table->in.heredoc)
		{
			table->in.fd = open("tmp/heredoc_tmp", O_RDONLY);
			if (table->in.fd == -1)
			{
				perror("open failed");
				return (0);
			}
			if (table->in.fd != 0 && table->type == SIMPLE_CMD)
			{
				dup2(table->in.fd, STDIN_FILENO);
				close(table->in.fd);
			}
		}
		else
		{
			table->in.fd = open(table->in.file_name[i], O_RDONLY);
			if (table->in.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->in.file_name[i]);
				return (0);
			}
			if (table->in.fd != 0 && table->type == SIMPLE_CMD)
			{
				dup2(table->in.fd, STDIN_FILENO);
				close(table->in.fd);
			}
		}
	}
	return (1);
}

int	open_out_files(t_cmd *table)
{
	int	i;

	if (table->out.file_name)
    {
		i = 0;
		while (table->out.file_name[i + 1])
		{
			if (table->out.trunc[i])
				table->out.fd = open(table->out.file_name[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				table->out.fd = open(table->out.file_name[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (table->out.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->out.file_name[i]);
				return (0);
			}
			if (close(table->out.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->in.file_name[i]);
				return (0);
			}
			i++;
		}
		if (table->out.trunc[i])
			table->out.fd = open(table->out.file_name[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			table->out.fd = open(table->out.file_name[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (table->out.fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(table->out.file_name[i]);
			return (0);
		}
		if (table->type == SIMPLE_CMD)
		{
			dup2(table->out.fd, STDOUT_FILENO);
			close(table->out.fd);
		}
    }
	return (1);
}