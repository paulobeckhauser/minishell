/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init_single_token_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:35:11 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/18 14:05:58 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	init_simple_cmd_token(t_prompt *prompt)
{
	t_token	token;

	token.type = SIMPLE_CMD;
	token.t_value.double_ptr = prompt->arr;
	return (token);
}
