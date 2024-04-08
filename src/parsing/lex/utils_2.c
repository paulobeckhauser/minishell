/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:14:57 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/07 19:56:49 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	skip_whitespaces(t_prompt *prompt)
{
	while (ft_strchr(prompt->whitespace, *prompt->msg)
		&& *prompt->msg)
		prompt->msg++;
}

int	get_word_length(t_prompt *prompt)
{
	int		len;
	int		i;
	char	curr_quote;

	len = 0;
	i = 0;
	curr_quote = 0;
	while (prompt->msg[i])
	{
		if (ft_strchr(prompt->whitespace, prompt->msg[i])
			|| ft_strchr(prompt->symbols, prompt->msg[i]))
			break ;
		if (ft_strchr(prompt->quotes, prompt->msg[i]))
			return (count_len_inside_quotes(prompt, i));
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

int	count_len_inside_quotes(t_prompt *prompt, int i)
{
	char	curr_quote;
	int		len;

	curr_quote = prompt->msg[i++];
	len = 0;
	while (prompt->msg[i])
	{
		if (prompt->msg[i] == curr_quote)
		{
			if (!prompt->msg[i + 1] || (prompt->msg[i + 1]
					&& (ft_strchr(prompt->symbols, prompt->msg[i + 1])
						|| ft_strchr(prompt->whitespace,
							prompt->msg[i + 1]))))
				return (len);
			++i;
			break ;
		}
		i++;
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
	t_type	type;

	type = find_token(prompt);
	if (type == PIPE)
		return ("|");
	else if (type == REDIRECTION)
		return (verify_redirection(prompt));
	else
		return (NULL);
}
