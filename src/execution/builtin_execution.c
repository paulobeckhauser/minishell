/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:59:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 14:20:35 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_execution(t_info *structure)
{
	int flag_cur_folder;
	flag_cur_folder = get_path_env(structure);
	
	if (!open_files(structure->table))
	{
		structure->last_exit_status = EXIT_FAILURE;
		return ;
	}
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
	if (is_env_command(structure->table->arr) && flag_cur_folder != 0)
		execute_env_command(structure);
	else if (is_env_command(structure->table->arr) && flag_cur_folder == 0)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		structure->last_exit_status = 127;
	}
	if (is_exit_command(structure->table->arr))
		execute_exit_command(structure);
}
