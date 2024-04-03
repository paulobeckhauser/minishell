/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_number_equal_signs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:40:44 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:18:04 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	count_number_equal_signs(int i, char **envp_sorted, t_info *structure)
{
	int	j;

	j = 0;
	structure->count_number_signs = 0;
	while (envp_sorted[i][j])
	{
		if (envp_sorted[i][j] == '=')
			structure->count_number_signs++;
		j++;
	}
}
