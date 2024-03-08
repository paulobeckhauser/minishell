/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:26:18 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/08 23:33:06 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_symbols_and_whitespace_strings(t_input_data *input_data)
{
	input_data->symbols = "|<>";
	input_data->whitespace = " \t\r\n\v";
	input_data->word_count = 0;
}

void	skip_whitespaces(t_input_data *input_data)
{
	while (ft_strchr(input_data->whitespace, *input_data->input) && *input_data->input)
		input_data->input++;
}

char	*verify_redirection(t_input_data *input_data)
{
	if (*input_data->input != *(input_data->input + 1))
	{
		if (*input_data->input == '<')
			return ("<");
		else
			return (">");
	}
	else
	{
		if (*input_data->input == '<')
			return ("<<");
		else
			return (">>");
	}
}

int	get_word_length(t_input_data *input_data)
{
	int	len;

	len = 0;
	while (!ft_strchr(input_data->symbols, input_data->input[len]) && input_data->input[len])
		len++;
	return (len);
}
