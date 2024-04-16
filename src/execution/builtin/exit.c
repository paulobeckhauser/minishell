/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/16 12:30:24 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_exit_command(char **command)
{
	return (ft_strcmp(command[0], "exit") == 0);
}

void	execute_exit_command(t_info *structure)
{
	int	nb;
	int	nb_args;

	nb_args = 0;
	while (structure->table->arr[nb_args])
		nb_args++;
	if (nb_args == 1)
	{
		printf("%s\n", structure->table->arr[0]);
		structure->last_exit_status = EX_SUCESS;
		exit(0);
	}
	else if (nb_args == 2)
	{
		if (ft_strcmp(structure->table->arr[1], "0") == 0)
		{
			structure->last_exit_status = 0;
			exit(0);
		}
		else
		{
			nb = ft_atoi(structure->table->arr[1]);
			printf("%s\n", structure->table->arr[0]);
			if (nb == 0)
			{
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(structure->table->arr[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				structure->last_exit_status = EX_NUM_REQ;
			}
			else
			{
				structure->last_exit_status = nb;
				exit(nb);
			}
		}
	}
	else
	{
		printf("%s\n", "exit");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
	}
}
