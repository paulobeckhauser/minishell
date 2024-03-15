/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/15 14:27:56 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int is_export_command(char **command)
{
    return(ft_strcmp(command[0], "export") == 0);
}

void    execute_export_command(char **command, char **envp)
{
    int i;

    if (command[1] == NULL)
    {
        i = 0;
        while(envp[i])
        {
            printf("declare -x %s\n", envp[i]);
            i++;
        }

    }
    else
    {
        
        char **name;

        name = ft_split(command[1], '=');

        printf("%s\n", name[0]);
        printf("%s\n", name[1]);

        
        
        
        
        // i = 0;
        // while(envp[i])
        // {
        //     // printf("%s\n", envp[i]);
        //     i++;
        // }

        
        
    }



    // envp[i] = "test=test";
    // envp[i + 1] = NULL;

    // i = 0;
    // while(envp[i])
    // {
    //     printf("%s\n", envp[i]);
    //     i++;
    // }



    // char *char_path = getenv("PATH");

    // printf("\n%s\n", char_path);

    // char *char_test = getenv("test");

    // printf("\n%s\n", char_test);
    

    // size_t
    // printf("export function\n");


    // char *key = command[1];
    // char *value = command[2];
    // int len;
    // char * str;


    // len = ft_strlen(key) + ft_strlen(value) + 2;

    // char *string;

    // string = ft_split(command[1], '=');

    // printf("%s\n", command[0]);
    // printf("%s\n", command[1]);
    // printf("%s\n", command[2]);

    // char **str;

    // str = ft_split(command[1], '=');

    // // printf("%s\n", str[0]);
    // // printf("%s\n", str[1]);

    // // printf("export command\n");


    // int i;

    // i = 0;

    // // while (structure->envp[i])
    // // {
    // //     printf("%s\n", structure->envp[i]);
    // //     i++;
    // // }

    // while(structure->envp[i])
    // {
    //     // if(ft_strncmp(structure->envp[i], str[0]))

    //     // printf("%s\n", structure->envp[i]);
    //     // printf("%s\n", str[0]);

    //     // int comparison;

    //     // comparison = ft_strncmp(structure->envp[i], str[0], ft_strlen(str[0]));
    //     // printf("%d\n", comparison);


    //     if (ft_strncmp(structure->envp[i], str[0], ft_strlen(str[0])) == 0 && structure->envp[i][ft_strlen(str[0]) == '='])
    //         return;
    //         // printf("There is\n");
        
    //     i++;
    // }

    // char **new_environ = malloc((i + 2) * sizeof(char *));
    // if (new_environ == NULL)
    // {
    //     perror("malloc");
    //     return;
    // }

    

    
    // str = malloc(len);
    // if (str == NULL)
    // {
    //     perror("malloc");
    //     return;
    // }

    //     // Create the string "key=value".
    // snprintf(str, len, "%s=%s", key, value);
    
    


}