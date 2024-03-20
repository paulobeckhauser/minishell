/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/20 13:12:17 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

static void	sort_env_variables(char **envp)
{
	int		length;
	int		i;
	int		j;
	int		j_min;
	char	*temp;

	length = 0;
	while (envp[length])
		length++;
	i = 0;
	while (i < length - 1)
	{
		j_min = i;
		j = i + 1;
		while (j < length)
		{
			if (strcmp(envp[j], envp[j_min]) < 0)
			{
				j_min = j;
			}
			j++;
		}
		if (j_min != i)
		{
			temp = envp[i];
			envp[i] = envp[j_min];
			envp[j_min] = temp;
		}
		i++;
	}
}

void	execute_export_command(char **command, char **envp)
{
	int		length;
	int		i;
	char	**array;
	int		j;
	int		j_min;
	char	*temp;
		char *str;
	char	*sig;
	char	*quote;

	if (command[1] == NULL)
	{
		sort_env_variables(envp);
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
	else
	{
		sig = "=";
		quote = "\"";
		array = ft_split(command[1], '=');
		i = 0;
		while (envp[i])
		{
			i++;
		}
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
