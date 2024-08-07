/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:03 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/23 21:26:42 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: edge_cases_handle
 * ----------------------------
 * Handles edge cases for export command arguments.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * i: The index of the current argument being processed.
 * 
 * Checks if the current argument starts with '-', '@', '#', or a number, which are not valid
 * identifiers for environment variables. If an invalid identifier is found, an error message
 * is printed, and the last exit status is set to failure.
 * 
 * Returns 1 if an edge case is handled, otherwise returns 0.
 */
static int	edge_cases_handle(t_info *structure, int i)
{
	int	j;
	int	flag_edge_cases;

	flag_edge_cases = 0;
	j = 0;
	if (((structure->table->arr[i][j] == '-'
			|| structure->table->arr[i][j] == '@'
		|| structure->table->arr[i][j] == '#')
			&& (structure->table->arr[i][j + 1] != '-'))
		|| (structure->table->arr[i][j + 1] == '-')
		|| (structure->table->arr[i][j] >= '0'
			&& structure->table->arr[i][j] <= '9'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(structure->table->arr[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
		flag_edge_cases = 1;
	}
	return (flag_edge_cases);
}

/* Function: iter_and_check
 * -------------------------
 * Iterates through an argument and prints it as part of an error message.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * i: The index of the current argument being processed.
 * 
 * This function is called when an argument contains a '-' immediately before an '=' sign,
 * which is not valid. It prints the entire argument as part of an error message and sets
 * the last exit status to 1.
 */
static void	iter_and_check(t_info *structure, int i)
{
	int	j;

	j = 0;
	ft_putstr_fd("minishell: export: `", 2);
	while (structure->table->arr[i][j])
	{
		ft_putchar_fd(structure->table->arr[i][j], 2);
		j++;
	}
	ft_putstr_fd("': not a valid identifier\n", 2);
	structure->last_exit_status = 1;
}

/* Function: change_envp
 * ----------------------
 * Updates the environment variables based on the current argument.
 * 
 * check_equal_sign: Indicates if the current argument contains an '=' sign.
 * structure: A pointer to the main structure containing the command arguments.
 * k: The index of the current argument being processed.
 * 
 * If the current argument contains an '=', it calls replace_value_envp to update the
 * environment variable. If not, it checks if the environment variable already exists
 * and updates it accordingly.
 */
static void	change_envp(int check_equal_sign, t_info *structure, int k)
{
	if (check_equal_sign == 1)
	{
		replace_value_envp(structure, check_equal_sign);
	}
	else
	{
		if (check_env_variable(structure))
		{
			return ;
		}
		else
		{
			add_to_envp(structure, structure->table->arr[k], check_equal_sign);
		}
	}
}

/* Function: nb_equal_signs
 * -------------------------
 * Counts the number of '=' signs in the current argument.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * i: The index of the current argument being processed.
 * 
 * Iterates through the argument to find an '=' sign. If a '-' is found immediately before
 * an '=', it calls iter_and_check and breaks the loop. Otherwise, it increments the count
 * of '=' signs found.
 * 
 * Returns the count of '=' signs found in the argument.
 */
static int	nb_equal_signs(t_info *structure, int i)
{
	int	check_equal_sign;
	int	j;

	j = 0;
	check_equal_sign = 0;
	while (structure->table->arr[i][j])
	{
		if (structure->table->arr[i][j] == '=')
		{
			if (structure->table->arr[i][j - 1] && structure->table->arr[i][j
				- 1] == '-')
			{
				iter_and_check(structure, i);
				break ;
			}
			check_equal_sign++;
			break ;
		}
		j++;
	}
	return (check_equal_sign);
}

/* Function: export_with_args
 * ---------------------------
 * Processes the export command with arguments.
 * 
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * Iterates through each argument provided to the export command. If the argument is "=",
 * "@", or "#", it prints an error message. Otherwise, it handles edge cases, counts the
 * number of '=' signs, and updates the environment variables accordingly.
 */
void	export_with_args(t_info *structure)
{
	int	check_equal_sign;
	int	i;

	i = 1;
	while (structure->table->arr[i])
	{
		if (ft_strcmp(structure->table->arr[i], "=") == 0
			|| ft_strcmp(structure->table->arr[i], "@") == 0
			|| ft_strcmp(structure->table->arr[i], "#") == 0)
		{
			ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
			structure->last_exit_status = 1;
		}
		else
		{
			if (edge_cases_handle(structure, i) == 0)
			{
				check_equal_sign = 0;
				check_equal_sign = nb_equal_signs(structure, i);
				change_envp(check_equal_sign, structure, i);
			}
		}
		i++;
	}
}