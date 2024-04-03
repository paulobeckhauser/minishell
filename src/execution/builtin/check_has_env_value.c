/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_has_env_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:11:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:18:58 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	check_has_env_value(int i, char **envp_sorted, t_info *structure)
{
	int	j;

	j = 0;
	while (envp_sorted[i][j] && envp_sorted[i][j] != '=')
		j++;
	if (envp_sorted[i][j + 1])
		structure->has_value_envp = 1;
	else
		structure->has_value_envp = 0;
}
