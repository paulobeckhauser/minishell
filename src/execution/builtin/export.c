/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/21 11:47:25 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

static void	execution_without_args(char **envp, int i, char **array)
{
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

void	execute_export_command(char **command, char **envp)
{
	int		length;
	int		i;
	char	**array;

	if (command[1] == NULL)
		execution_without_args(envp, i, array);
	else
	{
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
}
