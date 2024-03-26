/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/26 21:51:32 by pabeckha         ###   ########.fr       */
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
	// while(command[1][j])
	while(structure->table->arr[1][j])
	{
		// if (command[1][j] == '=')
		if (structure->table->arr[1][j] == '=')
		{
			check++;
			break;
		}
		j++;		
	}

	if (check == 1)
	{
		printf("Will add value\n");
	}

	// printf("%d\n", check);

	// if (check == 1)
	// {
	// 	execute_unset_command(structure);
		// delete_string(char *str_delete, char **array)
		// printf("%s\n", array[0]);
		// execute_unset_command(array[0], &envp);

		
		
		// array = ft_split(arr[1], '=');

		// if (check_env_variable(envp, array[0]))
		// if (check_env_variable(envp, command))
		// {
		// 	// execute_unset_command(command, &envp);
		// 	// delete_string(array[0], char **array)
		// 	printf("env exist\n");
		// }

		
		
		// i = 0;
		// while (envp[i])
		// 	i++;
		// if (array[1])
		// {
		// 	envp[i] = ft_strdup(command[1]);
		// 	i++;
		// 	envp[i] = NULL;
		// }
		// else
		// {
		// 	envp[i] = ft_strdup(array[0]);
		// 	i++;
		// 	envp[i] = NULL;
		// }	
		
	// }
	else
	{
		

		// printf("will only add the name\n");
	// else
	// {
		if (check_env_variable(structure))
		{
			// printf("env exist\n");
			return;
		}
		else
		{
			add_to_envp(structure);
		}
	}
	// 	else
	// 	{
		
		
	// 		// array = ft_split(command[1], '=');
	// 		// i = 0;
	// 		// while (structure->envp[i])
	// 		// 	i++;
	// 		// if (array[1])
	// 		// {
	// 		// 	structure->envp[i] = ft_strdup(command[1]);
	// 		// 	i++;
	// 		// 	structure->envp[i] = NULL;
	// 		// }
	// 		// else
	// 		// {
	// 		// 	structure->envp[i] = ft_strdup(array[0]);
	// 		// 	i++;
	// 		// 	structure->envp[i] = NULL;
	// 		// }	
	// 	}
	// }
	
	// array = ft_split(command[1], '=');

	
	// if (check_env_variable(envp, command))
	// {
	// 	printf("Variable already exist!\n");
	// 	printf("%s\n", command[1]);
		
		
	// }
		
	// else
	// 	printf("Variable does not existe\n");


	// array = ft_split(command[1], '=');
	// i = 0;
	// while (envp[i])
	// 	i++;
	// if (array[1])
	// {
	// 	envp[i] = ft_strdup(command[1]);
	// 	i++;
	// 	envp[i] = NULL;
	// }
	// else
	// {
	// 	envp[i] = ft_strdup(array[0]);
	// 	i++;
	// 	envp[i] = NULL;
	// }
}

void	execute_export_command(t_info *structure)
{
	char	**array;

	if (structure->table->arr[1] == NULL)
		export_without_args(structure);
		// export_without_args(*envp, array);
	// if (command[1] == NULL)
	// 	export_without_args(*envp, array);
		// printf("export without argcs\n");
	else
		export_with_args(structure);
		// printf("export with argcs\n");
}
