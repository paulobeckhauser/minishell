/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/21 18:29:21 by pabeckha         ###   ########.fr       */
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
		string = ft_strdup("\n");
	redirection_echo(string, structure);
	free(string);
}
