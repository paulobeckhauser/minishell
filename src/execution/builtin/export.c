/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/21 22:50:23 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

static void	export_without_args(char **envp, char **array)
{
	int	i;

	selectiton_sort_variables(envp);
	i = 0;
	while (envp[i])
	{
		array = ft_split(envp[i], '=');
		if (array[1])
			printf("declare -x %s=\"%s\"\n", array[0], array[1]);
		else
			printf("declare -x %s\n", envp[i]);
		free_2d_array(array);
		i++;
	}
}

//check if env variable already exists
// static int check_env_variable()
// {
	
// }

static void	export_with_args(char **array, char **command, char **envp)
{
	int	i;



	// printf("%s\n", command[0]);
	// printf("%s\n", command[1]);
	// int iter;

	// iter = 0;

	// while (envp[iter])
	// {
		
		
	// 	printf("%s\n", envp[iter]);
	// 	iter++;
	// }
	

	
	


	

	array = ft_split(command[1], '=');
	i = 0;
	while (envp[i])
		i++;
	if (array[1])
	{
		envp[i] = ft_strdup(command[1]);
		i++;
		envp[i] = NULL;
	}
	else
	{
		envp[i] = ft_strdup(array[0]);
		i++;
		envp[i] = NULL;
	}
}

void	execute_export_command(char **command, char **envp)
{
	char	**array;

	if (command[1] == NULL)
		export_without_args(envp, array);
	else
		export_with_args(array, command, envp);

	
	
}
