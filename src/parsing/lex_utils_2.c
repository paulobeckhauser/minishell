/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:14:57 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/17 20:33:14 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_word_length(t_input *input)
{
	int	len;

	len = 0;
	while (!ft_strchr(input->symbols, input->input[len])
		&& input->input[len])
		len++;
	return (len);
}

char	*fetch_file_name(t_input *input)
{
	char	*file_name;
	char	*start_ptr_save;
	size_t	i;

	skip_whitespaces(input);
	i = 0;
	while (!ft_strchr(input->whitespace, input->input[i]) && !ft_strchr(input->symbols, input->input[i]))
		i++;
	if (i == 0)
		return (NULL);
	file_name = malloc(i + 1);
	if (!file_name)
		return (NULL);
	start_ptr_save = file_name;
	while (!ft_strchr(input->whitespace, *input->input) && !ft_strchr(input->symbols, *input->input))
		*file_name++ = *input->input++;
	return (start_ptr_save);
}

char	*find_next_token_to_print_in_err(t_input *input)
{
	t_type 	type;

	type = find_token(input);
	if (type == PIPE)
		return ("|");
	else if (type == REDIRECTION)
		return(verify_redirection(input));
	else
		return (NULL);
}
