/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_without_value.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:33:18 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 19:33:47 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void print_export_without_value(int i, char **envp_sorted)
{
    int j;
    
    j = 0;
    print_export_structure("declare -x ");
    while(envp_sorted[i][j])
    {
        ft_putchar_fd(envp_sorted[i][j], 1);
        j++;
    }
    ft_putchar_fd('\"', 1);
    ft_putchar_fd('\"', 1);
    ft_putchar_fd('\n', 1);
}
