/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:53:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/26 15:47:11 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_unset_command(char **command)
{
	return (ft_strcmp(command[0], "unset") == 0);
}

char **delete_string(char *str_delete, char **array)
{
    char **array_backup;
    char **env_var;

    int i;
    int count;
    i = 0;
    count = 0;
    while(array[i])
    {
        env_var = ft_split(array[i], '=');
        if (ft_strcmp(str_delete, env_var[0]) == 0)
            count++;            
        i++;
        free_2d_array(env_var);
    }

    array_backup = (char **)malloc((i - count + 1) * sizeof(char *));

    int j;
    j = 0;
    int g;
    g = 0;

    while (array[j])
    {
        env_var = ft_split(array[j], '=');

        if (ft_strcmp(str_delete, env_var[0]) != 0)
        {
            array_backup[g] = ft_strdup(array[j]);
            g++;
        }
        j++;
    }
    array_backup[g] = NULL;
    return (array_backup);
    
}

void	execute_unset_command(char **command, char ***envp)
{
	int i;
    int l;
    
	if (!command[1])
		return;
	else
	{
		if (check_env_variable(*envp, command) == 1)
			*envp = delete_string(command[1], *envp);
		else
			return ;
	
	}
}