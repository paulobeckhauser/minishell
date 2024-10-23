/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:14:57 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:21:17 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: skip_whitespaces
 * ---------------------------
 * Advances the prompt message pointer past any leading whitespace characters.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * 
 * This function iterates through the characters of the prompt message and advances
 * the message pointer for each whitespace character found, using a predefined set
 * of whitespace characters for comparison.
 */
void	skip_whitespaces(t_prompt *prompt)
{
	while (*prompt->msg && ft_strchr(prompt->whitespace, *prompt->msg))
		prompt->msg++;
}

/* Function: get_word_length
 * --------------------------
 * Calculates the length of the next word in the prompt message, considering quotes.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * 
 * Returns: The length of the next word.
 * 
 * This function iterates through the characters of the prompt message to calculate
 * the length of the next word. It handles quoted strings as single words and ignores
 * whitespace and symbols outside of quotes. If no word is found, it advances the message
 * pointer by two characters.
 */
int	get_word_length(t_prompt *prompt)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
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

/* Function: count_len_inside_quotes
 * ----------------------------------
 * Counts the length of a string inside quotes, starting from a given index.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * i: The index from which to start counting inside the quoted string.
 * 
 * Returns: The length of the string inside quotes.
 * 
 * This function iterates through the characters of the prompt message starting from
 * the given index, counting the length of the string inside quotes. It stops counting
 * when it encounters the matching closing quote, provided the next character is either
 * a symbol, whitespace, or the end of the string.
 */
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

/* Function: fetch_file_name
 * -------------------------
 * Extracts the file name from the prompt message.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * 
 * Returns: A dynamically allocated string containing the file name, or NULL if no
 * file name is found.
 * 
 * This function skips leading whitespaces and then calculates the length of the file
 * name. It allocates memory for the file name and calls process_file_name to fill the
 * allocated string with the file name. If the file name is empty, it returns NULL.
 */
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
		return (NULL);
	file_name = process_file_name(prompt, file_name, i + 1);
	return (file_name);
}

/* Function: process_file_name
 * ---------------------------
 * Processes the file name from the prompt message into a provided buffer.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * file_name: The buffer where the file name will be stored.
 * i: The size of the buffer.
 * 
 * Returns: The buffer filled with the file name.
 * 
 * This function iterates through the characters of the prompt message, handling
 * quoted strings by skipping the quotes and copying the content inside. It stops
 * copying when it encounters whitespace, a symbol, or the end of the buffer.
 */
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