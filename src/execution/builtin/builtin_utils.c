/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:10:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/26 19:21:07 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// check if env variable already exists
// int check_env_variable(char **envp, char **command)
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


int check_env_variable(t_info *structure)
{
	char *temp;
	int check_exist;
	
	int i;
	int j;
	int len;
	char *str_temp;

	check_exist = 0;
	i = 0;
	while(structure->envp[i])
	{
		len = 0;
		while(structure->envp[i][len] && structure->envp[i][len] != '=')
			len++;
		str_temp = (char *)malloc((len + 1) * sizeof(char));
		j = 0;
		while(structure->envp[i][j] && structure->envp[i][j] != '=')
		{
			str_temp[j] = structure->envp[i][j];
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
	return (check_exist);
}