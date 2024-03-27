/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/27 11:59:24 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

static void	export_without_args(t_info *structure)
{
	int	i;
	char **array;

	// selectiton_sort_variables(envp);
	// i = 0;
	// while (envp[i])
	// {
	// 	array = ft_split(envp[i], '=');
	// 	if (array[1])
	// 		printf("declare -x %s=\"%s\"\n", array[0], array[1]);
	// 	else
	// 		printf("declare -x %s\n", envp[i]);
	// 	free_2d_array(array);
	// 	i++;
	// }

	selectiton_sort_variables(structure->envp);
	i = 0;
	while (structure->envp[i])
	{
		array = ft_split(structure->envp[i], '=');
		if (array[1])
			printf("declare -x %s=\"%s\"\n", array[0], array[1]);
		else
			printf("declare -x %s\n", structure->envp[i]);
		free_2d_array(array);
		i++;
	}
}

// check if env variable already exists
// static int check_env_variable(char **envp, char **command)
// {
// 	char *temp;
// 	int check_exist;
	
// 	int i;
// 	int j;
// 	int len;
// 	char *str_temp;

// 	check_exist = 0;
// 	i = 0;
// 	while(envp[i])
// 	{
// 		len = 0;
// 		while(envp[i][len] && envp[i][len] != '=')
// 			len++;
// 		str_temp = (char *)malloc((len + 1) * sizeof(char));
// 		j = 0;
// 		while(envp[i][j] && envp[i][j] != '=')
// 		{
// 			str_temp[j] = envp[i][j];
// 			j++;
// 		}
// 		str_temp[j] = '\0';
// 		if (ft_strcmp(str_temp, command[1]) == 0)
// 		{
// 			check_exist = 1;
// 			break;
// 		}
// 		free(str_temp);
// 		i++;
// 	}	
// 	return (check_exist);
// }

static void	export_with_args(t_info *structure)
{
	int	i;
	int j;
	int check;
	char **array;

	check = 0;
	j = 0;
	while(structure->table->arr[1][j])
	{
		if (structure->table->arr[1][j] == '=')
		{
			check++;
			break;
		}
		j++;		
	}

	if (check == 1)
	{
		array = ft_split(structure->table->arr[1], '=');
		delete_string(structure, array[0]);
		add_to_envp(structure, structure->table->arr[1]);
		free_2d_array(array);
	}
	else
	{
		if (check_env_variable(structure))
			return;
		else
			add_to_envp(structure, structure->table->arr[1]);
	}
}

void	execute_export_command(t_info *structure)
{
	if (structure->table->arr[1] == NULL)
		export_without_args(structure);
	else
		export_with_args(structure);
}
