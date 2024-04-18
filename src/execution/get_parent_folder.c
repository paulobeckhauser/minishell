/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parent_folder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:00:27 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 20:32:50 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_size_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static char	*copy_str(char *updated_str, char *str_new, int i)
{
	int	iter;

	iter = 0;
	while (updated_str[iter] && iter <= i)
	{
		str_new[iter] = updated_str[iter];
		iter++;
	}
	str_new[iter] = '\0';
	free(updated_str);
	updated_str = ft_strdup(str_new);
	return (updated_str);
}

static char	*iterate_copy(char **arr, int elem, char *updated_str, char *str)
{
	char	*str_path;
	char	*str_new;
	int		i;
	int		j;

	str_path = ft_strjoin("/", arr[elem]);
	str_new = malloc(ft_strlen(updated_str) - ft_strlen(arr[elem])
			- ft_strlen("/") + 1);
	i = ft_strlen(updated_str) - 1;
	j = ft_strlen(str_path) - 1;
	while (str[i] && str_path[j] && str[i] == str_path[j])
	{
		i--;
		j--;
	}
	updated_str = copy_str(updated_str, str_new, i);
	free(str_new);
	free(str_path);
	return (updated_str);
}

char	*get_parent_folder(char *str)
{
	char	**arr;
	int		elem;
	char	*updated_str;

	arr = ft_split(str, '/');
	elem = get_size_arr(arr) - 1;
	updated_str = ft_strdup(str);
	while (elem > 0)
	{
		if (access(updated_str, X_OK) == 0)
			break ;
		updated_str = iterate_copy(arr, elem, updated_str, str);
		elem--;
	}
	return (updated_str);
}
