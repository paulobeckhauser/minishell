/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:53:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/26 21:02:55 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_unset_command(char **command)
{
	return (ft_strcmp(command[0], "unset") == 0);
}


void delete_string(t_info *structure)
{
    char **array_backup;
    char **env_var;

    int i;
    int count;
    i = 0;
    count = 0;
    while(structure->envp[i])
    {
        env_var = ft_split(structure->envp[i], '=');
        if (ft_strcmp(structure->table->arr[1], env_var[0]) == 0)
            count++;            
        i++;
        free_2d_array(env_var);
    }
    array_backup = (char **)malloc((i - count + 1) * sizeof(char *));

    int j;
    j = 0;
    int g;
    g = 0;

    while (structure->envp[j])
    {
        env_var = ft_split(structure->envp[j], '=');

        if (ft_strcmp(structure->table->arr[1], env_var[0]) != 0)
        {
            array_backup[g] = ft_strdup(structure->envp[j]);
            g++;
        }
        j++;
    }
    array_backup[g] = NULL;
    free_2d_array(structure->envp);

    int u = 0;

    while (array_backup[u])
        u++;

    structure->envp = (char **)malloc((u + 1) * sizeof(char *));
    int f = 0;

    while (array_backup[f])
    {
        structure->envp[f] = ft_strdup(array_backup[f]);
        f++;
    }
    structure->envp[f] = NULL;
    
}



void	execute_unset_command(t_info *structure)
{
	int i;
    int l;
    

    if (!structure->table->arr[1])
        return;
	else
	{
        if (check_env_variable(structure) == 1)
            delete_string(structure);  
		else
			return ;
	
	}
}