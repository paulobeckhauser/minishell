/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_concat_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:44:55 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 12:17:45 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: ft_initiate_vars
 * ---------------------------
 * Initializes variables used in the split_concat function.
 * 
 * i: Pointer to the index variable for iterating through the string.
 * j: Pointer to the index variable for the array of strings.
 * s_word: Pointer to the variable tracking the start index of a word.
 */
static void	ft_initiate_vars(size_t *i, int *j, int *s_word)
{
	*i = 0;
	*j = 0;
	*s_word = -1;
}

/* Function: word_count
 * --------------------
 * Counts the number of words in a string, separated by a specified character.
 * 
 * str: The string to be analyzed.
 * c: The character that separates words.
 * 
 * Returns: The number of words in the string.
 */
static int	word_count(const char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*str)
	{
		if (*str != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*str == c)
			x = 0;
		str++;
	}
	return (count);
}

/* Function: fill_word
 * -------------------
 * Creates a new string from a substring of the original string, concatenates a command to it,
 * and ensures the new string is properly null-terminated.
 * 
 * str: The original string.
 * start: The start index of the substring.
 * end: The end index of the substring.
 * command: The command to concatenate to the substring.
 * 
 * Returns: A new string that is the result of the concatenation.
 */
static char	*fill_word(const char *str, int start, int end, char *command)
{
	char	*word;
	int		i;
	int		len_command;
	int		total_size;

	if (command == NULL)
		return (NULL);
	len_command = ft_strlen(command);
	i = 0;
	total_size = end - start + 1 + 1 + len_command;
	word = (char *)ft_calloc(total_size, sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '/';
	i++;
	ft_strlcat(word, command, total_size);
	word[i + len_command] = '\0';
	return (word);
}

/* Function: split_concat
 * ----------------------
 * Splits a string into an array of strings at each occurrence of a specified character,
 * then concatenates a command to each string.
 * 
 * s: The string to be split.
 * c: The character that separates parts of the string.
 * command: The command to concatenate to each part of the string.
 * 
 * Returns: An array of strings, each with the command concatenated.
 */
char	**split_concat(char const *s, char c, char *command)
{
	char	**array;
	size_t	i;
	int		j;
	int		s_word;

	ft_initiate_vars(&i, &j, &s_word);
	array = ft_calloc((word_count(s, c) + 2), sizeof(char *));
	if (!array)
		return (NULL);
	while (i < ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			array[j] = fill_word(s, s_word, i, command);
			check_and_free(array, j);
			s_word = -1;
			j++;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}