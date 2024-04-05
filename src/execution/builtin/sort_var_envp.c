/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_var_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:56:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:01:25 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	get_lenght(char **envp)
{
	int	length;

	length = 0;
	while (envp[length])
		length++;
	return (length);
}

static int	str_compare(int j, int length, int j_min, char **envp)
{
	while (j < length)
	{
		if (ft_strcmp(envp[j], envp[j_min]) < 0)
			j_min = j;
		j++;
	}
	return (j_min);
}

void	allocate_mem_sort_var(t_info *structure)
{
	int	i;
	int	len;

	len = 0;
	while (structure->envp_export[len])
		len++;
	structure->envp_sorted = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	while (structure->envp_export[i])
	{
		structure->envp_sorted[i] = ft_strdup(structure->envp_export[i]);
		i++;
	}
	structure->envp_sorted[i] = NULL;
}

void	selectiton_sort_variables(char **envp)
{
	int		length;
	int		i;
	int		j;
	int		j_min;
	char	*temp;

	length = get_lenght(envp);
	i = 0;
	while (i < length - 1)
	{
		j_min = i;
		j = i + 1;
		j_min = str_compare(j, length, j_min, envp);
		if (j_min != i)
		{
			temp = envp[i];
			envp[i] = envp[j_min];
			envp[j_min] = temp;
		}
		i++;
	}
}
