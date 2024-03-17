/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/16 18:22:16 by pabeckha         ###   ########.fr       */
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


// char *ft_strtok(char *str, const char *delim)
// {
// 	int i;
// 	int j;
// 	// char charac;

// 	// i = 0;
// 	// j = 0;
// 	// while(str[i])
// 	// {
// 	// 	if (str[i] == delim[j])
// 	// 		i++;
// 	// }
// 	// printf("%d\n", i);

// 	return(str);
// }

int ft_putenv(char *string)
{
	char *name;
	char *name_2;

	// printf("%s\n", string);
	
	// strtok(string, "=");
	// name = strtok(string, "=");
	// printf("%s\n", string);

	// name_2 = ft_strtok(string, "=");

	// name_2 = ft_strtok("TEST=legal", "=");

	

	// name_2 = ft_strtrim(string, "=");

	// printf("%s\n", name);
	printf("%s\n", name_2);



	return (0);
	
}




int ft_setenv(const char *name, const char *value, int overwrite)
{
	size_t len;
	char *str;
	int result;
	
	if (!overwrite && getenv(name))
	{
		// The environment variable already exists and we don't want to overwrite it
		return (0);
	}

	// Calculate the length of the string we need to allocate
	len = ft_strlen(name) + ft_strlen(value) + 2; // +2 for the '=' and the null terminator
	
	// Allocate the string
	str = malloc(len);
	if (!str)
		return (-1);
	
	


	ft_strlcpy(str, name, ft_strlen(name) + 2);
	ft_strlcat(str, "=", ft_strlen(str) + 2);
	ft_strlcat(str, value, ft_strlen(value) + ft_strlen(str) + 1);

	// result = putenv(str);
	
	result = ft_putenv(str);

	// printf("%s\n", str);
	
	return (result);
	
}