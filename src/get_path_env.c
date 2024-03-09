/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:34 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/07 16:33:37 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_path_env(t_info *structure)
{
	int		i;
	int		len_path;
	char	*default_path;

	default_path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	i = 0;
	len_path = 0;
	while (structure->envp[i])
	{
		if (ft_strncmp(structure->envp[i], "PATHs=", 5) == 0)
		{
			len_path = ft_strlen(structure->envp[i]);
			break ;
		}
		i++;
	}
	if (!structure->envp[i])
		structure->path_env = ft_strdup(default_path);
	else
		structure->path_env = ft_strdup(structure->envp[i] + 5);
}
