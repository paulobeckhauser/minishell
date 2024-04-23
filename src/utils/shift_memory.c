/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:35:26 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 20:25:40 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shift_strings_left(char **arr, int index, int size)
{
	free(arr[index]);
	if (size == 1)
		return (0);
	ft_memmove(&arr[index], &arr[index + 1],
		(size - index - 1) * sizeof(char *));
	arr[size - 1] = NULL;
	return (1);
}
