/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:30:45 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 21:05:51 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_error_message(t_cmd *table, int i)
{
	ft_putstr_fd("minishell: ", 2);
	perror(table->in.file_name[i]);
}

static void	redirec_fd_simple_cmd(t_cmd *table)
{
	if (table->in.fd != 0 && table->type == SIMPLE_CMD)
	{
		dup2(table->in.fd, STDIN_FILENO);
		close(table->in.fd);
	}
}

static int	handle_file(t_cmd *table, int i)
{
	table->in.fd = open(table->in.file_name[i], O_RDONLY);
	if (table->in.fd == -1)
	{
		print_error_message(table, i);
		return (0);
	}
	if (close(table->in.fd) == -1)
	{
		print_error_message(table, i);
		return (0);
	}
	return (1);
}

static int	execute_opening(t_cmd *table, int i)
{
	if (table->in.heredoc)
	{
		table->in.fd = open("tmp/heredoc_tmp", O_RDONLY);
		if (table->in.fd == -1)
		{
			perror("open failed");
			return (0);
		}
		redirec_fd_simple_cmd(table);
	}
	else
	{
		table->in.fd = open(table->in.file_name[i], O_RDONLY);
		if (table->in.fd == -1)
		{
			print_error_message(table, i);
			return (0);
		}
		redirec_fd_simple_cmd(table);
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
			if (!handle_file(table, i))
				return (0);
			i++;
		}
		if (!execute_opening(table, i))
			return (0);
	}
	return (1);
}
