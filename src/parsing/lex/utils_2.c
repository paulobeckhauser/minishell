/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:14:57 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 12:02:48 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	skip_whitespaces(t_prompt *prompt)
{
	while (*prompt->msg && ft_strchr(prompt->whitespace, *prompt->msg))
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
		{
			len += count_len_inside_quotes(prompt, i);
			break ;
		}
		i++;
		len++;
	}
	if (!len)
		prompt->msg += 2;
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
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*fetch_file_name(t_prompt *prompt)
{
	char	*file_name;
	size_t	i;

	skip_whitespaces(prompt);
	i = 0;
	while (prompt->msg[i] && !ft_strchr(prompt->whitespace, prompt->msg[i])
		&& !ft_strchr(prompt->symbols, prompt->msg[i]))
	{
		if (ft_strchr(prompt->quotes, prompt->msg[i]))
		{
			i += count_len_inside_quotes(prompt, i);
			break ;
		}
		i++;
	}
	if (i == 0)
		return (NULL);
	file_name = malloc(i + 1);
	if (!file_name)
		mem_alloc_protection();
	file_name = process_file_name(prompt, file_name, i + 1);
	return (file_name);
}

char	*process_file_name(t_prompt *prompt, char *file_name, size_t i)
{
	char	curr_quote;
	size_t	y;

	y = 0;
	while (*prompt->msg && y < i)
	{
		if (ft_strchr(prompt->quotes, *prompt->msg))
		{
			curr_quote = *prompt->msg++;
			while (*prompt->msg && *prompt->msg != curr_quote)
				file_name[y++] = *prompt->msg++;
			if (*prompt->msg && *prompt->msg == curr_quote)
				prompt->msg++;
		}
		else if (ft_strchr(prompt->whitespace, *prompt->msg)
			|| ft_strchr(prompt->symbols, *prompt->msg))
			break ;
		else
			file_name[y++] = *prompt->msg++;
	}
	file_name[y] = 0;
	return (file_name);
}
