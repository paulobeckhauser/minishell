/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:44:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 12:00:46 by sfrankie         ###   ########.fr       */
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
		mem_alloc_protection();
	i = 0;
	while (envp[i])
	{
		array[i] = ft_strdup(envp[i]);
		if (array[i] == NULL)
			mem_alloc_protection();
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	store_envp(char **envp, t_info *structure)
{
	structure->envp = store_array(envp);
	structure->envp_export = store_array(envp);
}
