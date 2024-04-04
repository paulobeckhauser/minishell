/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/04 17:51:37 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_echo_command(char **command)
{
	return (ft_strcmp(command[0], "echo") == 0);
}

static char	*join_string_echo(int start, int after, t_info *structure,
		char *string)
{
	int	i;

	string = ft_strdup(structure->table->arr[start]);
	i = after;
	while (structure->table->arr[i])
	{
		string = ft_strjoin(string, " ");
		string = ft_strjoin(string, structure->table->arr[i]);
		i++;
	}
	return (string);
}

static void	redirection_echo(char *string, t_info *structure)
{
	if (structure->table->out.file_name)
		ft_putstr_fd(string, structure->table->out.fd);
	else
		ft_putstr_fd(string, STDOUT_FILENO);
}

void	execute_echo_command(t_info *structure)
{
	char	*string;
	int		n_flag;

	n_flag = 0;
	if (structure->table->arr[1])
	{
		if (ft_strcmp(structure->table->arr[1], "-n") == 0)
			n_flag = 1;
		if (n_flag)
		{
			if (structure->table->arr[2])
				string = join_string_echo(2, 3, structure, string);
			else
				string = ft_strdup("");
		}
		else
		{
			string = join_string_echo(1, 2, structure, string);
			string = ft_strjoin(string, "\n");
		}
	}
	else
		string = ft_strdup("\n");
	redirection_echo(string, structure);
}
