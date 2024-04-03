/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_structure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 16:42:54 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void print_export_structure(char *str_declare)
{
    int i;

    i = 0;
    while(str_declare[i])
    {
        ft_putchar_fd(str_declare[i], 1);
        i++;
    }
}
