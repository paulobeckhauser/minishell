/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_without_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:08:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/21 15:54:13 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*echo_without_flag(char *string, t_info *structure)
{
	// string = join_string_echo(1, structure);
	// string = ft_strjoin(string, "\n");
	// return (string);
    // char *temp;
    
    // temp = join_string_echo(1, structure);
    // if (string != NULL)
    //     free(string);
    // string = temp;
    // temp = ft_strjoin(string, "\n");
    // if (string != NULL)
    //     free(string);
    // string = temp;
    // return (string);
    char *backup_string;

    string = join_string_echo(1, structure);

    backup_string = ft_strdup(string);
    free(string);
    string = ft_strjoin(backup_string, "\n");
    free(backup_string);

    return (string);
    
}
