/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:30:45 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 20:31:20 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
