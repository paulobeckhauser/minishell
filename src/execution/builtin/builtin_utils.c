/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:10:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/04 12:47:05 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


int check_env_variable(char **array, t_info *structure)
{
	char *temp;
	int check_exist;
	int i;
	int j;
	int len;
	char *str_temp;

	check_exist = 0;
	i = 0;


	while(structure->envp_export[i])
	{
		len = 0;
		while(structure->envp_export[i][len] && structure->envp_export[i][len] != '=')
			len++;
		str_temp = (char *)malloc((len + 1) * sizeof(char));
		j = 0;
		while(structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
		{
			str_temp[j] = structure->envp_export[i][j];
			j++;
		}
		str_temp[j] = '\0';
		if (ft_strcmp(str_temp, structure->table->arr[1]) == 0)
		{
			check_exist = 1;
			break;
		}
		free(str_temp);
		i++;
	}
	return(check_exist);
}
