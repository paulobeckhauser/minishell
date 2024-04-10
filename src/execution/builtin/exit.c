/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:54:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/10 14:14:55 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_exit_command(char **command)
{
	return (ft_strcmp(command[0], "exit") == 0);
}

void	execute_exit_command(t_info *structure)
{

	if (!structure->table->arr[1])
	{
		structure->last_exit_status = EX_SUCESS;
		exit(0);
	}
	else if (structure->table->arr[1])
	{
		// structure->last_exit_status = structure->table->arr[1];
		printf("%s\n", structure->table->arr[1]);
		// exit(structure->table->arr[1]);
	}

	// else
	// {
	// 	if (ft_strcmp(structure->table->arr[1],"0") == 0)
	// 	{
			
	// 		printf("Exit with 0\n");

			
	// 	}

	// 	else
	// 	{
	// 		exit_status = ft_atoi(structure->table->arr[1]);
	// 		if (exit_status != 0)
	// 			printf("Is a digit\n");
	// 		else
	// 			printf("Not a digit\n");
			
	// 	}
		

	// 	// printf("%d\n", exit_status);
	// }
		// printf("%s\n", command[1]);

	// else if(ft_isdigit(command[1]))
	// {
	// 	printf("Is numeric\n");
	// }
	// else
	// 	printf("not numeric");
	// else if (command[1])
	// {
	// 	printf("exit\n");
	// 	printf("bash: exit: %s: numeric argument required\n", command[1]);
	// 	exit(0);
	// }
}
