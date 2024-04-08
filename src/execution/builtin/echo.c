/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/08 13:42:49 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"



int	is_echo_command(char **command)
{
	return (ft_strcmp(command[0], "echo") == 0);
}


static int check_dollar_sign(char *str)
{
	int i;
	int check_dollar_sign;


	check_dollar_sign = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
		{
			check_dollar_sign = 1;
			break;
		}
		i++;
	}
	return (check_dollar_sign);
}



static char	*join_string_echo(int start, t_info *structure)
{
	char *concat_str = "";

	int j;
	char *str_env;
	int count;

	count = 0;
	
	while(structure->table->arr[start])
	{
		if (count > 0)
			concat_str = ft_strjoin(concat_str, " ");
		concat_str = ft_strjoin(concat_str, structure->table->arr[start]);

		start++;
		count++;

	}



	
	return (concat_str);
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
				string = join_string_echo(2, structure);
			else
				string = ft_strdup("");
		}
		else
		{
			string = join_string_echo(1, structure);
			string = ft_strjoin(string, "\n");
		}
	}
	else
		string = ft_strdup("\n");
	redirection_echo(string, structure);
}
