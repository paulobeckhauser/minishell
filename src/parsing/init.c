/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:52:15 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 12:52:24 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_variables(t_input *input)
{
	input->start_ptr_save = NULL;
	input->pipe_count = 0;
	input->symbols = "|<>";
	input->whitespace = " \t\r\n\v";
}