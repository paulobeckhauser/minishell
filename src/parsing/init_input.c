/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:52:15 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 15:33:19 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_input(t_input *input)
{
	input = ft_memset(input, 0, sizeof(t_input));
	input->symbols = "|<>";
	input->whitespace = " \t\r\n\v";
}