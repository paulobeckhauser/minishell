/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_token_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:35:11 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 14:35:32 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	init_simple_cmd_token(t_input *input)
{
	t_token	token;

	token.type = SIMPLE_CMD;
	token.t_value.double_ptr = input->arr;
	return (token);
}
