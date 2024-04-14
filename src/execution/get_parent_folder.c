/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parent_folder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:00:27 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/14 11:00:28 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static int get_size_arr(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return (i);
}


char *get_parent_folder(char *str)
{

	int size_arr;
	char **arr;
	int elem;
	

	arr = ft_split(str, '/');
	size_arr = get_size_arr(arr);

	
	elem = size_arr - 1;


	int it_size;
	char *str_path;
	char *str_new;
	char *updated_str;
	int str_len;
	int i;
	int j;
	int iter;
	int str_path_len;

	updated_str = ft_strdup(str);
	it_size = elem;

	while(elem > 0)
	{
		if (access(updated_str, X_OK) == 0)
			break;
		
		str_path = ft_strjoin("/", arr[elem]);

		

		str_new = malloc(ft_strlen(updated_str) - ft_strlen(arr[elem]) - ft_strlen("/") + 1);

		str_len = ft_strlen(updated_str);
		str_path_len = ft_strlen(str_path);
		
		i = str_len - 1;
		j = str_path_len - 1;


		while (str[i] && str_path[j] && str[i] == str_path[j])
		{
			i--;
			j--;
		}


		iter = 0;

		while(updated_str[iter] && iter <= i)
		{
			str_new[iter] = updated_str[iter];
			iter++;
		}
		str_new[iter] = '\0';

		// printf("%s\n", str_new);

		free(updated_str);

		updated_str = ft_strdup(str_new);

		free(str_new);
		
		
		elem--;
	
		free(str_path);
	}

    return (updated_str);
	
}