/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:59:50 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/29 09:00:31 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void builtin_execution(t_info *structure)
{
    if (is_cd_command(structure->table->arr))
        execute_cd_command(structure->table->arr); // cd with only a relative or absolute path
    if (is_pwd_command(structure->table->arr))
        execute_pwd_command(structure->table->arr);
    if (is_echo_command(structure->table->arr))
        execute_echo_command(structure); // need to implement reedirection
    if (is_export_command(structure->table->arr))
        execute_export_command(structure);
    if (is_unset_command(structure->table->arr))
        execute_unset_command(structure);
    if (is_env_command(structure->table->arr))
        execute_env_command(structure->table->arr);
    if (is_exit_command(structure->table->arr))
        execute_exit_command(structure->table->arr);
}
