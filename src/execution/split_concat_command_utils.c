/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_concat_command_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:49:45 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/04 14:49:13 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**check_and_free(char **array, int j)
{
	if (!(array[j]))
	{
		ft_free(array, j);
		return (NULL);
	}
	return (array);
}
