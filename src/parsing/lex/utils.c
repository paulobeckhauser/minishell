/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:57:55 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:23:11 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: verify_redirection
 * ----------------------------
 * Checks the current character in the prompt message for redirection symbols
 * and advances the message pointer accordingly.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * 
 * Returns: A string representing the redirection symbol ("<", ">", "<<", ">>"),
 * or NULL if no redirection symbol is found at the current message position.
 * 
 * This function checks the current character in the prompt message for redirection
 * symbols ("<" or ">"). If a single symbol is found, it advances the message pointer
 * by one and returns the symbol. If a double symbol is found (indicating appending
 * or heredoc redirection), it advances the pointer by two and returns the double
 * symbol. If no redirection symbol is found, it returns NULL.
 */
char	*verify_redirection(t_prompt *prompt)
{
	if (*prompt->msg == '<' && *prompt->msg != *(prompt->msg + 1))
	{
		prompt->msg++;
		return ("<");
	}
	else if (*prompt->msg == '>' && *prompt->msg != *(prompt->msg + 1))
	{
		prompt->msg++;
		return (">");
	}
	else if (*prompt->msg == '<' && *prompt->msg == *(prompt->msg + 1))
	{
		prompt->msg += 2;
		return ("<<");
	}
	else if (*prompt->msg == '>' && *prompt->msg == *(prompt->msg + 1))
	{
		prompt->msg += 2;
		return (">>");
	}
	else
		return (NULL);
}

/* Function: count_words
 * ---------------------
 * Counts the number of words in the prompt message, excluding symbols and
 * handling quotes properly.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * 
 * This function iterates through the prompt message, counting words. A word is
 * defined as a sequence of characters that does not include any symbols defined
 * in prompt->symbols, and is not inside quotes. Words inside quotes are counted
 * as a single word, regardless of whitespace or symbols inside the quotes. The
 * function also skips over any whitespace characters as defined in prompt->whitespace.
 */
void	count_words(t_prompt *prompt)
{
	char	*start_ptr_save;

	start_ptr_save = prompt->msg;
	prompt->word_count = 0;
	while (*prompt->msg)
	{
		if (ft_strchr(prompt->symbols, *prompt->msg))
			break ;
		else if (ft_strchr(prompt->quotes, *prompt->msg))
			count_words_inside_quotes(prompt, &start_ptr_save);
		else if (ft_strchr(prompt->whitespace, *prompt->msg))
			skip_whitespaces(prompt);
		else
		{
			if (prompt->msg == start_ptr_save || (*(prompt->msg - 1)
					&& !ft_strchr(prompt->quotes, *(prompt->msg - 1))))
				prompt->word_count++;
			while (*prompt->msg && !ft_strchr(prompt->symbols, *prompt->msg)
				&& !ft_strchr(prompt->quotes, *prompt->msg)
				&& !ft_strchr(prompt->whitespace, *prompt->msg))
				prompt->msg++;
		}
	}
	prompt->msg = start_ptr_save;
}

/* Function: count_words_inside_quotes
 * -----------------------------------
 * Counts a word inside quotes and advances the message pointer beyond the quotes.
 * 
 * prompt: A pointer to the prompt structure containing the message to be processed.
 * start_ptr_save: A pointer to the start of the message, used to determine if the
 * current position is the start of a new word.
 * 
 * This function counts a sequence of characters inside quotes as a single word,
 * regardless of the content. It advances the message pointer to the character
 * after the closing quote. If the quotes are empty or the quote character is
 * immediately followed by another quote character, it does not count as a word
 * and the function simply advances the pointer past the quotes.
 */
void	count_words_inside_quotes(t_prompt *prompt, char **start_ptr_save)
{
	char	curr_quote;

	curr_quote = *prompt->msg;
	if (*(prompt->msg + 1) && *(prompt->msg + 1) == curr_quote)
	{
		prompt->msg += 2;
		return ;
	}
	if (prompt->msg == *start_ptr_save
		|| ft_strchr(prompt->symbols, *(prompt->msg - 1))
		|| ft_strchr(prompt->whitespace, *(prompt->msg - 1)))
		prompt->word_count++;
	prompt->msg++;
	while (*prompt->msg && *prompt->msg != curr_quote)
		prompt->msg++;
	prompt->msg++;
}

/* Function: if_builtin_cmd
 * ------------------------
 * Checks if a given string matches any of the shell's built-in commands.
 * 
 * str: The string to check against the list of built-in commands.
 * 
 * Returns: 1 if the string matches a built-in command, 0 if it does not, and
 * -1 if there is an error allocating memory for the built-in commands list.
 * 
 * This function creates a list of built-in commands and checks if the given
 * string exactly matches any of them. If a match is found, it frees the list
 * of built-in commands and returns 1. If no match is found, it frees the list
 * and returns 0. If there is an error allocating memory for the list, it returns -1.
 */
int	if_builtin_cmd(char *str)
{
	char	**builtins;
	int		i;

	builtins = malloc(8 * sizeof(char *));
	if (!builtins)
		return (-1);
	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i] && str && *str)
	{
		if (ft_strncmp(builtins[i], str, ft_strlen(builtins[i])) == 0
			&& ft_strlen(builtins[i]) == ft_strlen(str))
			return (free(builtins), 1);
		i++;
	}
	free(builtins);
	return (0);
}