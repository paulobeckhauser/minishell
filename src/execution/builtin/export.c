/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 12:47:07 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

void	execute_export_command(t_info *structure)
{
	if (structure->table->arr[1] == NULL)
		export_without_args(structure);
	else
		export_with_args(structure);
}
