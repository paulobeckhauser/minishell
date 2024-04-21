/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_without_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:08:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/21 13:29:31 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*echo_without_flag(char *string, t_info *structure)
{
    string = join_string_echo(1, structure);
    string = ft_strjoin(string, "\n");
    return (string);
}