/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 21:44:22 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_exit_command(char **command)
{
	return (ft_strcmp(command[0], "exit") == 0);
}

static void	exit_1_arg(t_info *structure)
{
	printf("%s\n", structure->table->arr[0]);
	structure->last_exit_status = EX_SUCESS;
	exit(0);
}

static void	exit_2_args(t_info *structure)
{
	int	nb;

	nb = 0;
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
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(structure->table->arr[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			structure->last_exit_status = EX_NUM_REQ;
			exit(EX_NUM_REQ);
		}
		else
		{
			structure->last_exit_status = nb;
			exit(nb);
		}
	}
}

static void	exit_more_args(t_info *structure)
{
	int nb;

	nb = ft_atoi(structure->table->arr[1]);
	printf("%s\n", "exit");
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if(nb == 0)
	{
		
		structure->last_exit_status = 2;
		exit(2);
	}
	else
	{
		structure->last_exit_status = 1;
		exit(1);
	}
}

void	execute_exit_command(t_info *structure)
{
	int	nb_args;

	nb_args = 0;
	while (structure->table->arr[nb_args])
		nb_args++;
	if (nb_args == 1)
		exit_1_arg(structure);
	else if (nb_args == 2)
		exit_2_args(structure);
	else
		exit_more_args(structure);
}
