/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:44:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 16:00:01 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**store_array(char **envp)
{
	int		i;
	char	**array;

	i = 0;
	while (envp[i])
		i++;
	array = (char **)malloc((i + 1) * sizeof(char *));
	if (array == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		array[i] = (char *)malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
		if (array[i] == NULL)
		{
			perror("Memory allocation failed!\n");
			exit(EXIT_FAILURE);
		}
		array[i] = ft_strdup(envp[i]);
		i++;
	}
	return (array);
}

void	store_envp(char **envp, t_info *structure)
{
	structure->envp = store_array(envp);
	structure->envp_export = store_array(envp);
}
