/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dollar_sign_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:28:23 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:18:12 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: measure_dollar_word_len
 * ----------------------------------
 * Measures the length of a word following a dollar sign until a whitespace,
 * another dollar sign, or the end of the string is encountered.
 * 
 * str: Pointer to the string being analyzed.
 * prompt: Struct containing shell information, including whitespace characters.
 * len: Pointer to an integer where the length of the word will be stored.
 * 
 * This function iterates over the characters of a string starting from a
 * dollar sign, counting the number of characters until a stopping condition
 * is met. The length is stored in the provided integer pointer.
 */
void	measure_dollar_word_len(char **str, t_prompt *prompt, int *len)
{
	*len = 0;
	while (**str != '\0' && !ft_strchr(prompt->whitespace, **str)
		&& **str != '$')
	{
		(*len)++;
		(*str)++;
	}
}

/* Function: replace_dollar_word
 * ------------------------------
 * Replaces a word starting with a dollar sign with its corresponding value
 * from the environment variables.
 * 
 * structure: Struct containing environment variables.
 * str: The word to be replaced.
 * 
 * Returns a pointer to the replaced word or NULL if no replacement is found.
 * 
 * This function iterates through the environment variables, looking for a
 * match with the provided word. If a match is found, the value of the
 * environment variable is returned as the replacement.
 */
char	*replace_dollar_word(t_info *structure, char *str)
{
	char	*str_temp;
	int		i;

	i = 0;
	while (structure->envp_export[i])
	{
		str_temp = allocate_str_temp(structure, str_temp, i);
		str_temp = save_str_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, str) == 0)
		{
			free(str_temp);
			return (extract_dollar_value(structure->envp_export[i]));
		}
		i++;
		free(str_temp);
	}
	return (NULL);
}

/* Function: extract_dollar_value
 * -------------------------------
 * Extracts the value of an environment variable from a string in the format
 * "KEY=VALUE".
 * 
 * str: The environment variable string.
 * 
 * Returns a pointer to the extracted value.
 * 
 * This function finds the '=' character in the string, then allocates and
 * copies everything after this character as the value to be returned.
 */
char	*extract_dollar_value(char *str)
{
	char	*word_replacement;
	char	*start_ptr_save;

	while (*str)
	{
		if (*str++ == '=')
			break ;
	}
	word_replacement = malloc(ft_strlen(str) + 1);
	if (!word_replacement)
		return (NULL);
	start_ptr_save = word_replacement;
	while (*str)
		*word_replacement++ = *str++;
	*word_replacement = 0;
	word_replacement = start_ptr_save;
	return (word_replacement);
}

/* Function: replace_words_in_arr
 * -------------------------------
 * Replaces occurrences of a word starting with a dollar sign in an array
 * with its corresponding value.
 * 
 * prompt: Struct containing shell information.
 * i: Index of the command in the array where the replacement should occur.
 * dollar_word: The word to be replaced.
 * replacement: The replacement value for the word.
 * 
 * This function constructs the word to be replaced by adding a dollar sign
 * prefix, then searches for this word in the command array. If found, it
 * replaces the word with the provided replacement value.
 */
void	replace_words_in_arr(t_prompt *prompt, int i, char *dollar_word,
	char *replacement)
{
	t_dollar_replace_info	info;
	int						y;

	info.prompt = prompt;
	info.i = i;
	info.dollar_word = ft_strjoin("$", dollar_word);
	if (ft_strcmp(dollar_word, "?") && ft_strcmp(dollar_word, "$"))
		free(dollar_word);
	info.replacement = ft_strdup(replacement);
	free(replacement);
	y = 0;
	while (info.prompt->arr[info.i][y])
	{
		if (ft_strncmp(info.prompt->arr[info.i] + y, info.dollar_word,
				ft_strlen(info.dollar_word)) == 0)
		{
			replace_word(&info, y);
			return ;
		}
		else
			y++;
	}
}

/* Function: replace_word
 * -----------------------
 * Replaces a word in a string with another word.
 * 
 * info: Struct containing information for the replacement operation.
 * y: The starting index of the word to be replaced in the string.
 * 
 * This function creates a new string where the specified word is replaced
 * with the replacement value. It then updates the original string pointer
 * to point to this new string, freeing any necessary memory.
 */
void	replace_word(t_dollar_replace_info *info, int y)
{
	char	*new_str;
	char	*before_dollar;
	char	*after_dollar;
	int		dollar_word_len;

	dollar_word_len = ft_strlen(info->dollar_word);
	before_dollar = ft_substr(info->prompt->arr[info->i], 0, y);
	after_dollar = ft_substr(info->prompt->arr[info->i], y + dollar_word_len,
			ft_strlen(info->prompt->arr[info->i]) - y - dollar_word_len);
	new_str = malloc(ft_strlen(before_dollar) + ft_strlen(info->replacement)
			+ ft_strlen(after_dollar) + 1);
	ft_strlcpy(new_str, before_dollar, ft_strlen(before_dollar) + 1);
	ft_strlcat(new_str, info->replacement, ft_strlen(before_dollar)
		+ ft_strlen(info->replacement) + 1);
	ft_strlcat(new_str, after_dollar, ft_strlen(before_dollar)
		+ ft_strlen(info->replacement) + ft_strlen(after_dollar) + 1);
	free(info->prompt->arr[info->i]);
	info->prompt->arr[info->i] = new_str;
	free(info->dollar_word);
	free(info->replacement);
	free(before_dollar);
	free(after_dollar);
}