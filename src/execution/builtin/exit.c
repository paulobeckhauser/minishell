/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:21:41 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_exit_command(char **command)
{
	return (ft_strcmp(command[0], "exit") == 0);
}

void	execute_exit_command(char **command)
{
	exit(0);
}
