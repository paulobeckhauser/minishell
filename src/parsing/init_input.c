/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:52:15 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 17:48:06 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_prompt(t_prompt *prompt)
{
	prompt = ft_memset(prompt, 0, sizeof(t_prompt));
	prompt->symbols = "|<>";
	prompt->whitespace = " \t\r\n\v";
}
