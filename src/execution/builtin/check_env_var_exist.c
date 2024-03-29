/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var_exist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:10:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 11:18:57 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*allocate_mem_string(t_info *structure, int i)
{
	int		j;
	char	*str_temp;

	j = 0;
	while (structure->envp[i][j] && structure->envp[i][j] != '=')
		j++;
	str_temp = (char *)malloc((j + 1) * sizeof(char));
	if (str_temp == NULL)
		return (NULL);
	return (str_temp);
}

static char	*copy_string_temp(t_info *structure, int i, char *str_temp)
{
	int	j;

	j = 0;
	while (structure->envp[i][j] && structure->envp[i][j] != '=')
	{
		str_temp[j] = structure->envp[i][j];
		j++;
	}
	str_temp[j] = '\0';
	return (str_temp);
}

int	check_env_var_exist(t_info *structure)
{
	int		check_exist;
	int		i;
	int		j;
	char	*str_temp;

	check_exist = 0;
	i = 0;
	while (structure->envp[i])
	{
		str_temp = allocate_mem_string(structure, i);
		str_temp = copy_string_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, structure->table->arr[1]) == 0)
		{
			check_exist = 1;
			break ;
		}
		free(str_temp);
		i++;
	}
	return (check_exist);
}
