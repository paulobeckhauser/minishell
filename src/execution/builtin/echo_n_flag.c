/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:27:59 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/19 12:19:03 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"


int flag_string_only_n(char *str)
{
    int size_str;
    int count_n;
    int i;

    // printf("str inside function is: %s\n", str);
    size_str = ft_strlen(str);
    i = 0;
    count_n = 0;
    if (str[i] == '-')
    {
        i++;
        count_n++;
        while(str[i])
        {
            if (str[i] == 'n')
                count_n++;
            i++;
        }

    }
    if (size_str == count_n)
        return (1);
    return (0);
}


char *echo_n_flag(char *string, t_info *structure, int i)
{
    if (structure->table->arr[2])
    {
        while (structure->table->arr[i])
        {
            if (ft_strcmp(structure->table->arr[i], "-n") == 0)
                i++;
            else
                break;
        }
        if (structure->table->arr[i])
            string = join_string_echo(i, structure);
        else
            string = ft_strdup("");

    }
    else
        string = ft_strdup("");


    return (string);
}
