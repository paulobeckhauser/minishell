/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:38:08 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/26 21:56:38 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void add_to_envp(t_info *structure)
{
    char **backup_array;
    int i;
    int j;

    i = 0;

    while(structure->envp[i])
        i++;
    backup_array = (char **)malloc((i + 1) * sizeof(char *));
    
    j = 0;

    while(structure->envp[j])
    {
        backup_array[j] = ft_strdup(structure->envp[j]);
        j++;
    }

    free_2d_array(structure->envp);

    structure->envp = (char **)malloc((i + 2) * sizeof(char *));

    int k;
    k = 0;

    while (backup_array[k])
    {
        structure->envp[k] = ft_strdup(backup_array[k]);
        k++;
    }

    structure->envp[k] = ft_strdup(structure->table->arr[1]);
    k++;
    structure->envp[k] = NULL;

    free_2d_array(backup_array);
    
    
    

}