/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:59:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/14 22:11:04 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_execution(t_info *structure)
{
	if (!open_files(structure->table))
		structure->last_exit_status = EXIT_FAILURE;
	if (is_cd_command(structure->table->arr))
		execute_cd_command(structure);
	if (is_pwd_command(structure->table->arr))
		execute_pwd_command(structure->table->arr);
	if (is_echo_command(structure->table->arr))
		execute_echo_command(structure);
	if (is_export_command(structure->table->arr))
		execute_export_command(structure);
	if (is_unset_command(structure->table->arr))
		execute_unset_command(structure);
	if (is_env_command(structure->table->arr))
		execute_env_command(structure);
	if (is_exit_command(structure->table->arr))
		execute_exit_command(structure);
}
