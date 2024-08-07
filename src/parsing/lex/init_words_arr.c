/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_words_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:15:05 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:10:57 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_words_arr
 * -------------------------
 * Initializes the array of words from the user's input.
 * 
 * prompt: The current command prompt context, containing the user's input message.
 * 
 * This function dynamically allocates memory for an array of strings, where each
 * string represents a word from the user's input. It handles quotes, whitespace,
 * and symbols appropriately to accurately segment the input into words.
 */
void	init_words_arr(t_prompt *prompt)
{
	t_init_words_arr_vars	vars;

	vars.i = 0;
	prompt->arr = ft_calloc(prompt->word_count + 1, sizeof(char *));
	if (!prompt->arr)
		return ;
	init_single_quote_checker_list(prompt);
	while (*prompt->msg)
	{
		if (ft_strchr(prompt->symbols, *prompt->msg))
			break ;
		else if (ft_strchr(prompt->whitespace, *prompt->msg))
			skip_whitespaces(prompt);
		else
		{
			vars.j = 0;
			vars.word_len = get_word_length(prompt);
			if (vars.word_len == 0)
				continue ;
			process_word(prompt, vars.word_len, vars.i, &vars.j);
			vars.i++;
		}
	}
	prompt->arr[vars.i] = NULL;
}

/* Function: process_word
 * -----------------------
 * Processes a single word from the user's input.
 * 
 * prompt: The current command prompt context.
 * word_len: The length of the word to be processed.
 * i: The index in the array where the word will be stored.
 * j: A pointer to an integer tracking the position within the current word.
 * 
 * This function allocates memory for a single word and copies characters from
 * the user's input into this newly allocated space. It handles quotes by only
 * ending the word when the matching quote is found, allowing for spaces and
 * symbols to be included within quoted segments.
 */
void	process_word(t_prompt *prompt, int word_len, int i, int *j)
{
	char	curr_quote;

	prompt->arr[i] = malloc(word_len + 1);
	if (!prompt->arr[i])
		return ;
	while (*prompt->msg && *j < word_len)
	{
		if (ft_strchr(prompt->quotes, *prompt->msg))
		{
			curr_quote = *prompt->msg++;
			if (curr_quote == '\'')
				update_single_quote_status(prompt, i);
			while (*prompt->msg && *prompt->msg != curr_quote)
				prompt->arr[i][(*j)++] = *prompt->msg++;
			if (*prompt->msg && *prompt->msg == curr_quote)
				prompt->msg++;
		}
		else if (ft_strchr(prompt->whitespace, *prompt->msg)
			|| ft_strchr(prompt->symbols, *prompt->msg))
			break ;
		else
			prompt->arr[i][(*j)++] = *prompt->msg++;
	}
	prompt->arr[i][*j] = 0;
}