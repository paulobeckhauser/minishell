/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:14:57 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 13:15:25 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token init_builtin_cmd_token(t_input *input)
{
	t_token	token;

	token.type = BUILTIN_CMD;
	token.t_value.double_ptr = input->arr;
	return (token);
}

void	skip_whitespaces(t_input *input)
{
	while (ft_strchr(input->whitespace, *input->input)
		&& *input->input)
		input->input++;
}

int	get_word_length(t_input *input)
{
	int	len;

	len = 0;
	while (!ft_strchr(input->symbols, input->input[len])
		&& input->input[len])
		len++;
	return (len);
}
