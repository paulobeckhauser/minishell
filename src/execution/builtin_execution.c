/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:59:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/13 16:43:41 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_execution(t_info *structure)
{
	if (structure->table->in.file_name)
	{
		int k = 0;
		while (structure->table->in.file_name[k + 1])
		{
			structure->table->in.fd = open(structure->table->in.file_name[k], O_RDONLY);
			if (structure->table->in.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(structure->table->in.file_name[k]);
				structure->last_exit_status = EXIT_FAILURE;
				return ;
			}
			if (close(structure->table->in.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(structure->table->in.file_name[k]);
				structure->last_exit_status = EXIT_FAILURE;
				return ;
			}
			k++;
		}
		if (structure->table->in.heredoc)
		{
			structure->table->in.fd = open("tmp/heredoc_tmp", O_RDONLY);
			if (structure->table->in.fd == -1)
			{
				perror("open failed");
				structure->last_exit_status = EXIT_FAILURE;
				return ;
			}
		}
		else
		{
			structure->table->in.fd = open(structure->table->in.file_name[k], O_RDONLY);
			if (structure->table->in.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(structure->table->in.file_name[k]);
				structure->last_exit_status = EXIT_FAILURE;
				return ;
			}
			if (structure->table->in.fd != 0 && structure->table->in.fd != -1)
			{
				dup2(structure->table->in.fd, STDIN_FILENO);
				close(structure->table->in.fd);
			}
		}
	}
	if (structure->table->out.file_name)
    {
		int	l = 0;
		while (structure->table->out.file_name[l + 1])
		{
			if (structure->table->out.trunc[l])
				structure->table->out.fd = open(structure->table->out.file_name[l], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				structure->table->out.fd = open(structure->table->out.file_name[l], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (structure->table->out.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(structure->table->out.file_name[l]);
				exit(EXIT_FAILURE);
			}
			if (close(structure->table->out.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(structure->table->in.file_name[l]);
				exit(EXIT_FAILURE);
			}
			l++;
		}
		if (structure->table->out.trunc[l])
			structure->table->out.fd = open(structure->table->out.file_name[l], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			structure->table->out.fd = open(structure->table->out.file_name[l], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (structure->table->out.fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(structure->table->out.file_name[l]);
			exit(EXIT_FAILURE);
		}
        dup2(structure->table->out.fd, STDOUT_FILENO);
        close(structure->table->out.fd);
    }
	if (is_cd_command(structure->table->arr))
		execute_cd_command(structure);
	if (is_pwd_command(structure->table->arr))
		execute_pwd_command(structure->table->arr);
	if (is_echo_command(structure->table->arr))
		execute_echo_command(structure);
	if (is_export_command(structure->table->arr))
		execute_export_command(structure);
	if (is_unset_command(structure->table->arr))
		execute_unset_command(structure);
	if (is_env_command(structure->table->arr))
		execute_env_command(structure);
	if (is_exit_command(structure->table->arr))
		execute_exit_command(structure);
}
