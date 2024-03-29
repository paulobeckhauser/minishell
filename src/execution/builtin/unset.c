/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:53:40 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 11:14:43 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_unset_command(char **command)
{
	return (ft_strcmp(command[0], "unset") == 0);
}

void	execute_unset_command(t_info *structure)
{
	if (!structure->table->arr[1])
		return ;
	else
	{
		if (check_env_var_exist(structure) == 1)
			delete_string_in_array(structure, structure->table->arr[1]);
		else
			return ;
	}
}
