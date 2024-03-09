/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:09:37 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/08 17:13:28 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void check_builtin(t_info *structure, char *str)
{
    if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0 
        || ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0 
            || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "exit") == 0)
    {
        
        structure->is_builtin = 1;
        // printf("IS BUILTIN\n");
    }
    else
        structure->is_builtin = 0;
}