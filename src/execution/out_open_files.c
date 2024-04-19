/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_open_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:32:54 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 20:39:24 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
