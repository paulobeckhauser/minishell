/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:34:49 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/23 17:41:01 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: exit_1_arg
 * ---------------------
 * Handles the exit command when there is only one argument.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * This function prints the command name and sets the last exit status to success.
 * It then exits the program with a status of 0.
 */
void	exit_1_arg(t_info *structure)
{
	printf("%s\n", structure->table->arr[0]);
	structure->last_exit_status = EX_SUCESS;
	exit(0);
}

/* Function: handle_not_numeric
 * -----------------------------
 * Handles the case when the exit command argument is not numeric.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * Prints an error message indicating that a numeric argument is required.
 * Sets the last exit status to the error code for numeric argument required
 * and exits the program with this status.
 */
static void	handle_not_numeric(t_info *structure)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(structure->table->arr[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	structure->last_exit_status = EX_NUM_REQ;
	exit(EX_NUM_REQ);
}

/* Function: exit_2_args
 * ----------------------
 * Handles the exit command when there are two arguments.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * This function checks if the second argument is "0". If so, it sets the last exit
 * status to 0 and exits the program with a status of 0. If the second argument is not
 * "0", it attempts to convert it to an integer. If the conversion results in 0, indicating
 * that the argument is not numeric, it calls handle_not_numeric. Otherwise, it sets the
 * last exit status to the converted number and exits the program with this status.
 */
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

/* Function: exit_more_args
 * -------------------------
 * Handles the exit command when there are more than two arguments.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * This function attempts to convert the second argument to an integer. It then prints
 * an error message indicating that too many arguments were provided. If the conversion
 * results in 0, it sets the last exit status to 2 and exits the program with this status.
 * Otherwise, it sets the last exit status to 1 and exits the program with this status.
 */
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