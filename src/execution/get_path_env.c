/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:34 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/10 22:06:10 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_path_env(t_info *structure)
{
	int		i;
	int		len_path;
	int		j;
	char	*str_temp;
	int		k;
	int		m;
	int		p;
	int		count;

	if (structure->envp_export == NULL)
		return (0);
	i = 0;
	j = 0;
	len_path = 0;
	count = 0;

	structure->path_env = NULL;
	
	while (structure->envp_export[i])
	{
		str_temp = allocate_str_temp(structure, str_temp, i);
		str_temp = save_str_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, "PATH") == 0)
		{
			count++;
			while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
			{
				j++;
			}
			k = j + 1;
			j++;
			m = 0;
			while (structure->envp_export[i][j])
			{
				m++;
				j++;
			}
			structure->path_env = (char *)malloc((m + 1) * sizeof(char));
			p = 0;
			while (structure->envp_export[i][k])
			{
				structure->path_env[p] = structure->envp_export[i][k];
				k++;
				p++;
			}
			structure->path_env[p] = '\0';
		}
		free(str_temp);
		i++;
	}

	return (count);

	
	
	// if (!count)
	// {
	// 	printf("THERE IS NO PATH!\n");
	// }
	// 	structure->path_env = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
}
