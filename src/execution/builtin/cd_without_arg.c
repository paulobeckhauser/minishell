/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_without_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:18:02 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:39:39 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: ret_len_home_if_exists
 * --------------------------------
 * Checks if the "HOME" environment variable exists and returns the length of its name.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * i: The index of the current environment variable being checked.
 * 
 * Returns the count of characters matching the "HOME" string.
 * 
 * This function iterates through the characters of the current environment variable name
 * and compares them with the "HOME" string. It increments a counter for each matching character.
 * The function returns this counter, which can be used to check if the "HOME" variable exists.
 */
static int	ret_len_home_if_exists(t_info *structure, int i)
{
	int		j;
	int		count;
	char	*home;

	home = "HOME";
	j = 0;
	count = 0;
	while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
	{
		if (structure->envp_export[i][j] == home[j])
			count++;
		j++;
	}
	return (count);
}

/* Function: allocate_mem_string
 * -----------------------------
 * Allocates memory for the path of the "HOME" directory.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * i: The index of the "HOME" environment variable.
 * j: The starting index of the path in the environment variable string.
 * 
 * Returns a pointer to the allocated string for the "HOME" path.
 * 
 * This function calculates the length of the "HOME" path and allocates memory for it.
 * It returns a pointer to the allocated memory. If memory allocation fails, it prints
 * an error message and returns NULL.
 */
static char	*allocate_mem_string(t_info *structure, int i, int j)
{
	int		m;
	int		l;
	char	*path_home;

	path_home = NULL;
	m = j;
	l = 0;
	while (structure->envp_export[i][m])
	{
		m++;
		l++;
	}
	path_home = ft_calloc(l + 1, sizeof(char));
	if (!path_home)
	{
		perror("Memory allocation problem\n");
		return (NULL);
	}
	return (path_home);
}

/* Function: go_to_home_folder
 * ---------------------------
 * Changes the current working directory to the "HOME" directory.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * i: The index of the "HOME" environment variable.
 * 
 * This function extracts the path of the "HOME" directory from the environment variable,
 * allocates memory for it, and changes the current working directory to this path.
 * It then frees the allocated memory.
 */
static void	go_to_home_folder(t_info *structure, int i)
{
	int		j;
	int		k;
	int		t;
	char	*path_home;

	j = 0;
	path_home = NULL;
	while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
		j++;
	j++;
	path_home = allocate_mem_string(structure, i, j);
	k = j;
	t = 0;
	while (structure->envp_export[i][k])
	{
		path_home[t] = structure->envp_export[i][k];
		k++;
		t++;
	}
	path_home[t] = '\0';
	execute_handle_error_cd(path_home, structure);
	free(path_home);
}

/* Function: check_if_home_exists
 * ------------------------------
 * Checks if the "HOME" environment variable exists and changes the directory accordingly.
 * 
 * check: A flag indicating if the "HOME" variable exists.
 * i: The index of the "HOME" environment variable.
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * If the "HOME" variable exists, this function changes the current working directory to the "HOME" directory.
 * If it does not exist, it prints an error message and sets the last exit status to failure.
 */
static void	check_if_home_exists(int check, int i, t_info *structure)
{
	if (check)
		go_to_home_folder(structure, i);
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
	}
}

/* Function: cd_wihtout_args
 * -------------------------
 * Changes the current working directory to the "HOME" directory when no arguments are provided to cd.
 * 
 * structure: A pointer to the main structure containing the environment variables.
 * 
 * This function iterates through the environment variables to find the "HOME" variable.
 * If found, it changes the current working directory to the "HOME" directory.
 * If the "HOME" variable is not set, it prints an error message and sets the last exit status to failure.
 */
void	cd_wihtout_args(t_info *structure)
{
	int		i;
	int		count;
	char	*home;
	int		len;
	int		check;

	home = "HOME";
	i = 0;
	count = 0;
	len = ft_strlen(home);
	check = 0;
	while (structure->envp_export[i])
	{
		count = ret_len_home_if_exists(structure, i);
		if (count == len)
		{
			check = 1;
			break ;
		}
		i++;
	}
	check_if_home_exists(check, i, structure);
}