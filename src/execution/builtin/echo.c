/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/22 17:07:25 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_echo_command(char **command)
{
	return (ft_strcmp(command[0], "echo") == 0);
}

void	execute_echo_command(char **command, int fd)
{
	char *string;

	string = ft_strdup(command[1]);

	ft_strlcat(string, "\n", ft_strlen(string) + 2);
	ft_putstr_fd(string, fd);
}
