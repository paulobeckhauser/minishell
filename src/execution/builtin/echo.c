/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 13:08:57 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_echo_command(char **command)
{
	return (ft_strcmp(command[0], "echo") == 0);
}

static void	redirection_echo(char *string, t_info *structure)
{
	if (structure->table->out.file_name)
	{
		ft_putstr_fd(string, structure->table->out.fd);
		if (close(structure->table->out.fd) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror("close");
			return ;
		}
	}
	else
		ft_putstr_fd(string, STDOUT_FILENO);
}

static char	*condition_flag(int n_flag, char *string, t_info *structure, int i)
{
	if (n_flag)
		string = echo_n_flag(string, structure, i);
	else
		string = echo_without_flag(string, structure);
	return (string);
}

static char	*duplicate_newline(void)
{
	char	*string;

	string = ft_strdup("\n");
	if (string == NULL)
		mem_alloc_protection();
	return (string);
}

void	execute_echo_command(t_info *structure)
{
	char	*string;
	int		n_flag;
	int		i;

	n_flag = 0;
	string = NULL;
	i = 1;
	if (structure->table->arr[1])
	{
		while (structure->table->arr[i])
		{
			if (flag_string_only_n(structure->table->arr[i]))
			{
				n_flag = 1;
				i++;
			}
			else
				break ;
		}
		string = condition_flag(n_flag, string, structure, i);
	}
	else
		string = duplicate_newline();
	redirection_echo(string, structure);
	free(string);
}
