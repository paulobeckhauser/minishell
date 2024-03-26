/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:53:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/26 20:52:28 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_unset_command(char **command)
{
	return (ft_strcmp(command[0], "unset") == 0);
}

// char **delete_string(char *str_delete, char **array)
// {
//     char **array_backup;
//     char **env_var;

//     int i;
//     int count;
//     i = 0;
//     count = 0;
//     while(array[i])
//     {
//         env_var = ft_split(array[i], '=');
//         if (ft_strcmp(str_delete, env_var[0]) == 0)
//             count++;            
//         i++;
//         free_2d_array(env_var);
//     }

//     array_backup = (char **)malloc((i - count + 1) * sizeof(char *));

//     int j;
//     j = 0;
//     int g;
//     g = 0;

//     while (array[j])
//     {
//         env_var = ft_split(array[j], '=');

//         if (ft_strcmp(str_delete, env_var[0]) != 0)
//         {
//             array_backup[g] = ft_strdup(array[j]);
//             g++;
//         }
//         j++;
//     }
//     array_backup[g] = NULL;
//     return (array_backup);
    
// }

// void	execute_unset_command(char **command, char ***envp)
// {
// 	int i;
//     int l;
    
// 	if (!command[1])
// 		return;
// 	else
// 	{
// 		if (check_env_variable(*envp, command) == 1)
//         {
//             printf("%s\n", command[1]);
//             printf("hello\n");
// 			*envp = delete_string(command[1], *envp);
//         }
// 		else
// 			return ;
	
// 	}
// }


void delete_string(t_info *structure)
{
    char **array_backup;
    char **env_var;

    int i;
    int count;
    i = 0;
    count = 0;

    // printf("%s\n", structure->table->arr[1]);
    
    

    while(structure->envp[i])
    {
        env_var = ft_split(structure->envp[i], '=');
        if (ft_strcmp(structure->table->arr[1], env_var[0]) == 0)
            count++;            
        i++;
        free_2d_array(env_var);
    }

    // printf("Count: %d\n", count);

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


    
    // int d = 0;
    // while(structure->envp[d])
    // {
    //     // printf("%s\n", structure->envp[d]);
    //     free(structure->envp[d]);
    //     d++;
    // }


    

    free_2d_array(structure->envp);

    int u = 0;

    while (array_backup[u])
    {
        u++;
    }

    structure->envp = (char **)malloc((u + 1) * sizeof(char *));

    
    int f = 0;

    while (array_backup[f])
    {
        structure->envp[f] = ft_strdup(array_backup[f]);
        f++;
    }
    structure->envp[f] = NULL;
    
}


// void	execute_unset_command(char **command, char ***envp)
void	execute_unset_command(t_info *structure)
{
	int i;
    int l;
    
	// if (!command[1])
	// 	return;



    // int m;


    // m = 0;
    // while(structure->envp[m])
    // {
    //     printf("%s\n", structure->envp[m]);
    //     m++;
    // }
    // printf("%s\n", structure->table->arr[1]);

    if (!structure->table->arr[1])
        return;
	else
	{
		// if (check_env_variable(structure->envp, structure->table->arr) == 1)
        if (check_env_variable(structure) == 1)
        {
            delete_string(structure);


            

            
        }
		else
			return ;
	
	}
}