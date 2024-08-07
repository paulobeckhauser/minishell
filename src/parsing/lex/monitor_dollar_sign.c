/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:53:32 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:19:13 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: verify_dollar
 * ------------------------
 * Checks and processes dollar signs ($) in the command array.
 * 
 * structure: Struct containing environment variables.
 * prompt: Struct containing shell information.
 * 
 * Returns 1 if successful, 0 otherwise.
 * 
 * This function iterates through the command array, skipping over parts that
 * are within single quotes. If a dollar sign is found, it attempts to handle
 * it with handle_dollar. If handle_dollar returns 0, it tries to shift the
 * strings in the array to the left. If handle_dollar returns 2, it breaks
 * the loop.
 */
int	verify_dollar(t_info *structure, t_prompt *prompt)
{
	int						i;
	int						ex;
	t_single_quote_checker	*head;

	i = 0;
	ex = 0;
	head = prompt->checker;
	while (prompt->arr[i] && prompt->checker)
	{
		if (if_single_quoted_str(&prompt->checker, &i))
			continue ;
		while (prompt->arr[i] && ft_strchr(prompt->arr[i], '$'))
		{
			ex = handle_dollar(structure, prompt, prompt->arr[i], &i);
			if (!ex)
			{
				if (!shift_strings_left(prompt->arr, i, prompt->word_count))
					return (0);
			}
			else if (ex == 2)
				break ;
		}
		i++;
	}
	return (prompt->checker = head, free_single_quote_checker_list(prompt), 1);
}

/* Function: if_single_quoted_str
 * -------------------------------
 * Checks if the current string is within single quotes.
 * 
 * checker: Pointer to a struct tracking single-quoted strings.
 * i: Pointer to the current index in the command array.
 * 
 * Returns 1 if the current string is within single quotes, 0 otherwise.
 * 
 * This function checks if the current string is marked as being within single
 * quotes by the checker. If so, it increments the index and moves to the next
 * checker node.
 */
int	if_single_quoted_str(t_single_quote_checker **checker, int *i)
{
	if (*checker && (*checker)->index == *i
		&& (*checker)->single_quoted)
	{
		(*i)++;
		*checker = (*checker)->next;
		return (1);
	}
	*checker = (*checker)->next;
	return (0);
}

/* Function: handle_dollar
 * ------------------------
 * Handles a string containing a dollar sign ($).
 * 
 * structure: Struct containing environment variables.
 * prompt: Struct containing shell information.
 * str: The string containing the dollar sign.
 * i: Pointer to the current index in the command array.
 * 
 * Returns 1 if the dollar sign was successfully handled, 2 if the dollar sign
 * should be ignored, or 0 if an error occurred.
 * 
 * This function identifies the word following the dollar sign and attempts to
 * replace it with its corresponding value from the environment variables. If
 * the word is a special case (e.g., "$$" or "$?"), it is handled accordingly.
 */
int	handle_dollar(t_info *structure, t_prompt *prompt, char *str, int *i)
{
	char	*dollar_word;
	char	*word_replacement;

	dollar_word = find_dollar_word(prompt, str);
	if (ft_strcmp(dollar_word, "$") == 0)
	{
		replace_words_in_arr(prompt, *i, "$", getpid_from_stat(prompt));
		return (1);
	}
	if (ft_strcmp(dollar_word, "") == 0)
		return (2);
	if (ft_strcmp(dollar_word, "?") == 0)
	{
		replace_words_in_arr(prompt, *i, dollar_word,
			ft_itoa(structure->last_exit_status));
		return (1);
	}
	word_replacement = replace_dollar_word(structure, dollar_word);
	if (!word_replacement)
		return (free(dollar_word), 0);
	replace_words_in_arr(prompt, *i, dollar_word, word_replacement);
	return (1);
}

/* Function: find_dollar_word
 * ---------------------------
 * Finds the word following a dollar sign in a string.
 * 
 * prompt: Struct containing shell information.
 * str: The string containing the dollar sign.
 * 
 * Returns the word following the dollar sign, or an empty string if no valid
 * word is found.
 * 
 * This function skips past the dollar sign and identifies the word that
 * follows it, stopping at whitespace, another dollar sign, or the end of the
 * string. Special cases like "$$", "$?", and an immediate following whitespace
 * are handled separately.
 */
char	*find_dollar_word(t_prompt *prompt, char *str)
{
	int		len;
	int		i;
	char	*dollar_word;
	char	*dollar_start;

	move_pointer_after_dollar(&str);
	if (!*str || ((*str) && ft_strchr(prompt->whitespace, *str)))
		return ("");
	if (*str == '$')
		return ("$");
	if (*str == '?')
		return ("?");
	dollar_start = str;
	measure_dollar_word_len(&str, prompt, &len);
	str = dollar_start;
	dollar_word = malloc(len + 1);
	if (!dollar_word)
		return (NULL);
	i = 0;
	while (*str && !ft_strchr(prompt->whitespace, *str)
		&& !ft_strchr(prompt->off_symbols, *str))
		dollar_word[i++] = *str++;
	return (dollar_word[i] = 0, dollar_word);
}

/* Function: move_pointer_after_dollar
 * ------------------------------------
 * Moves the pointer to the character immediately after the first dollar sign.
 * 
 * str: Pointer to the string pointer being manipulated.
 * 
 * This function iterates through the string until it finds a dollar sign, then
 * moves the pointer to the character immediately following the dollar sign.
 */
void	move_pointer_after_dollar(char **str)
{
	while (**str)
	{
		if (**str == '$')
		{
			++(*str);
			break ;
		}
		++(*str);
	}
}