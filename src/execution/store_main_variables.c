/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_main_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:44:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/12 13:45:30 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void store_main_arguments(int argc, char **argv, char **envp, t_info *structure)
{
    structure->argc = argc;
    structure->argv = argv;
	structure->envp = envp;
}