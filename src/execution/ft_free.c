/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:47:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/08 17:13:37 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void free_2d_array(char **array)
{
    int i;

    i = 0;
    while(array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}