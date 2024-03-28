/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:14:57 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/28 11:27:54 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_whitespaces(t_prompt *prompt)
{
	while (ft_strchr(prompt->whitespace, *prompt->msg)
		&& *prompt->msg)
		prompt->msg++;
}

int	get_word_length(t_prompt *prompt)
{
	int		len;
	char	curr_quote;
	len = 0;
	curr_quote = 0;
	if (ft_strchr(prompt->quotes, prompt->msg[len]))
	{
		curr_quote = prompt->msg[len++];
		while (prompt->msg[len] && prompt->msg[len] != curr_quote)
			len++;
	}
	else
	{
		while (!ft_strchr(prompt->symbols, prompt->msg[len])
			&& prompt->msg[len])
			len++;
	}
	return (len);
}

char	*fetch_file_name(t_prompt *prompt)
{
	char	*file_name;
	char	*start_ptr_save;
	size_t	i;

	skip_whitespaces(prompt);
	i = 0;
	while (!ft_strchr(prompt->whitespace, prompt->msg[i])
		&& !ft_strchr(prompt->symbols, prompt->msg[i]))
		i++;
	if (i == 0)
		return (NULL);
	file_name = malloc(i + 1);
	if (!file_name)
		return (NULL);
	start_ptr_save = file_name;
	while (!ft_strchr(prompt->whitespace, *prompt->msg)
		&& !ft_strchr(prompt->symbols, *prompt->msg))
		*file_name++ = *prompt->msg++;
	*file_name = 0;
	return (start_ptr_save);
}

char	*find_next_token_to_print_in_err(t_prompt *prompt)
{
	t_type 	type;

	type = find_token(prompt);
	if (type == PIPE)
		return ("|");
	else if (type == REDIRECTION)
		return(verify_redirection(prompt));
	else
		return (NULL);
}
