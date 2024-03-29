/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:53:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 17:03:52 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_unset_command(char **command)
{
	return (ft_strcmp(command[0], "unset") == 0);
}


static char **delete_string_array(char **array, char *str_delete)
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
    free_2d_array(array);

    int u = 0;

    while (array_backup[u])
        u++;

    array = (char **)malloc((u + 1) * sizeof(char *));
    int f = 0;

    while (array_backup[f])
    {
        array[f] = ft_strdup(array_backup[f]);
        f++;
    }
    array[f] = NULL;
    return (array);
}

void delete_string(t_info *structure, char *str_delete)
{
    structure->envp = delete_string_array(structure->envp, str_delete);
    structure->envp_export = delete_string_array(structure->envp_export, str_delete);
}



void	execute_unset_command(t_info *structure)
{
	int i;
    int l;
    

    if (!structure->table->arr[1])
        return;
	else
	{
        
        if (check_env_variable(structure->envp ,structure) == 1)
            delete_string(structure, structure->table->arr[1]);
        else if(check_env_variable(structure->envp_export ,structure) == 1)
            structure->envp_export = delete_string_array(structure->envp_export, structure->table->arr[1]);
		else
			return ;
	
	}
}