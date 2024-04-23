/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:34:49 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/23 17:41:01 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	exit_1_arg(t_info *structure)
{
	printf("%s\n", structure->table->arr[0]);
	structure->last_exit_status = EX_SUCESS;
	exit(0);
}

static void	handle_not_numeric(t_info *structure)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(structure->table->arr[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	structure->last_exit_status = EX_NUM_REQ;
	exit(EX_NUM_REQ);
}

void	exit_2_args(t_info *structure)
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
			handle_not_numeric(structure);
		else
		{
			structure->last_exit_status = nb;
			exit(nb);
		}
	}
}

void	exit_more_args(t_info *structure)
{
	int	nb;

	nb = ft_atoi(structure->table->arr[1]);
	printf("%s\n", "exit");
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (nb == 0)
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
