/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_main_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:44:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/26 19:56:10 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void store_main_arguments(int argc, char **argv, char **envp, t_info *structure)
{
    structure->argc = argc;
    structure->argv = argv;

    

    int i;

    i = 0;

    while (envp[i])
        i++;
    

    structure->envp = (char **)malloc((i + 1) * sizeof(char *));
    if(structure->envp == NULL)
    {
        perror("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    int j;
    int len;
    
    while (envp[j])
    {
        structure->envp[j] = (char *)malloc((ft_strlen(envp[j]) + 1) * sizeof(char));
        if(structure->envp[j] == NULL)
        {
            perror("Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        structure->envp[j] = ft_strdup(envp[j]);
        j++;
    }    

    
    // printf("%d\n", i);

    
	// structure->envp = envp;
}