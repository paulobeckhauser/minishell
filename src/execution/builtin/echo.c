/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/27 13:55:16 by pabeckha         ###   ########.fr       */
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

	i = 0;
	while(structure->table->arr[i])
	{
		printf("%s\n", structure->table->arr[i]);
		i++;
		
	}
	// string = ft_strdup(command[1]);

	// ft_strlcat(string, "\n", ft_strlen(string) + 2);
	// ft_putstr_fd(string, fd);
}
