/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_main_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:44:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/28 16:12:58 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	store_envp(char **envp, t_info *structure)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	structure->envp = (char **)malloc((i + 1) * sizeof(char *));
	if (structure->envp == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		structure->envp[i] = (char *)malloc((ft_strlen(envp[i]) + 1)
				* sizeof(char));
		if (structure->envp[i] == NULL)
		{
			perror("Memory allocation failed!\n");
			exit(EXIT_FAILURE);
		}
		structure->envp[i] = ft_strdup(envp[i]);
		i++;
	}
}
