/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:16:30 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/12 14:09:13 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../inc/minishell.h"

// void check_cd_command(char **command)
// {
//     if (ft_strcmp(command[0], "cd") == 0)
//     {
//         if (cd(command[1]) < 0)
//             perror(command[1]);
//         break;
//     }
// }

int cd(char *path)
{
    return(chdir(path));
}