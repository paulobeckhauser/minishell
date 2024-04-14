/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:57:30 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/14 21:34:48 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_files(t_cmd *table, int dev_null_fd)
{
	// if (table->in_prio)
	// {
		open_in_files(table, dev_null_fd);
		open_out_files(table);
	// }
	// else
	// {
	// 	open_out_files(table);
	// 	open_in_files(table, dev_null_fd);
	// }
}

void	open_in_files(t_cmd *table, int dev_null_fd)
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
				exit(EXIT_FAILURE);
			}
			if (close(table->in.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->in.file_name[i]);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		if (table->in.heredoc)
		{
			table->in.fd = open("tmp/heredoc_tmp", O_RDONLY);
			if (table->in.fd == -1)
			{
				perror("open failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			table->in.fd = open(table->in.file_name[i], O_RDONLY);
			if (table->in.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->in.file_name[i]);
				dup2(dev_null_fd, STDIN_FILENO);
				exit(EXIT_FAILURE);
			}
			if (table->in.fd != 0)
			{
				dup2(table->in.fd, STDIN_FILENO);
				close(table->in.fd);
			}
		}
	}
}

void	open_out_files(t_cmd *table)
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
				exit(EXIT_FAILURE);
			}
			if (close(table->out.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(table->in.file_name[i]);
				exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
		}
        dup2(table->out.fd, STDOUT_FILENO);
        close(table->out.fd);
    }
}