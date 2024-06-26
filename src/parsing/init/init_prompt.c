/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:24:27 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/20 18:42:19 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_prompt(t_prompt *prompt)
{
	prompt = ft_memset(prompt, 0, sizeof(t_prompt));
	prompt->symbols = "|<>";
	prompt->whitespace = " \t\r\v";
	prompt->quotes = "\"\'";
	prompt->off_symbols = "!@#$%^&*-+=()[]{}\\|:;,<>/?.";
}
