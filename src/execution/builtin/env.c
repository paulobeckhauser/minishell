/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:28 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/22 17:07:29 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_env_command(char **command)
{
	return (ft_strcmp(command[0], "env") == 0);
}

void	execute_env_command(char **command)
{
	printf("env\n");
}
