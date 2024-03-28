/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/28 14:59:29 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_echo_command(char **command)
{
	return (ft_strcmp(command[0], "echo") == 0);
}

void	execute_echo_command(char **command, int fd, t_info* structure)
{
	char *string;
	int i;
	

	if (structure->table->arr[1])
	{
		string = ft_strdup(structure->table->arr[1]);
		i = 2;
		while(structure->table->arr[i])
		{
			// string = ft_strjoin(string, structure->table->arr[i]);

			string = ft_strjoin(string, " ");
			string = ft_strjoin(string, structure->table->arr[i]);
			i++;
		}
		string = ft_strjoin(string, "\n");
	}
	else
		string = ft_strdup("\n");


	// printf("%s\n", string);

	// char *temp_arr;
	// i = 2;


	// i = 1;
	// while(structure->table->arr[i])
	// {
	// 	printf("%s ", structure->table->arr[i]);
	// 	i++;
		
	// }
	// printf("\n");
	// string = ft_strdup(command[1]);

	// ft_strlcat(string, "\n", ft_strlen(string) + 2);
	ft_putstr_fd(string, fd);

	// ft_strjoin()
}
