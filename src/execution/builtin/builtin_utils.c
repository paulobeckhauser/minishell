/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:10:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 11:04:17 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*allocate_str_temp(t_info *structure, char *str_temp, int i)
{
	int	len;

	len = 0;
	while (structure->envp_export[i][len]
		&& structure->envp_export[i][len] != '=')
		len++;
	str_temp = (char *)malloc((len + 1) * sizeof(char));
	if (str_temp == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return (str_temp);
}

char	*save_str_temp(t_info *structure, int i, char *str_temp)
{
	int	j;

	j = 0;
	while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
	{
		str_temp[j] = structure->envp_export[i][j];
		j++;
	}
	str_temp[j] = '\0';
	return (str_temp);
}

int	check_env_variable(t_info *structure)
{
	int		check_exist;
	int		i;
	char	*str_temp;

	check_exist = 0;
	i = 0;
	while (structure->envp_export[i])
	{
		str_temp = allocate_str_temp(structure, str_temp, i);
		str_temp = save_str_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, structure->table->arr[1]) == 0)
		{
			free(str_temp);
			check_exist = 1;
			break ;
		}
		free(str_temp);
		i++;
	}
	return (check_exist);
}
