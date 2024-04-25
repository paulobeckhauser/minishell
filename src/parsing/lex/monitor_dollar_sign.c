/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:53:32 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 12:02:32 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

int	handle_dollar(t_info *structure, t_prompt *prompt, char *str, int *i)
{
	char	*dollar_word;
	char	*word_replacement;

	dollar_word = find_dollar_word(prompt, str);
	if (ft_strcmp(dollar_word, "$") == 0)
	{
		replace_words_in_arr(prompt, *i, "$", getpid_from_stat());
		return (1);
	}
	if (ft_strcmp(dollar_word, "") == 0)
		return (2);
	if (ft_strcmp(dollar_word, "?") == 0)
	{
		replace_dollar_with_exit_status(structure, prompt, *i, dollar_word);
		return (1);
	}
	word_replacement = replace_dollar_word(structure, dollar_word);
	if (!word_replacement)
		return (free(dollar_word), 0);
	replace_words_in_arr(prompt, *i, dollar_word, word_replacement);
	return (1);
}

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
		mem_alloc_protection();
	i = 0;
	while (*str && !ft_strchr(prompt->whitespace, *str)
		&& !ft_strchr(prompt->off_symbols, *str))
		dollar_word[i++] = *str++;
	return (dollar_word[i] = 0, dollar_word);
}

void	replace_dollar_with_exit_status(t_info *structure, t_prompt *prompt,
	int i, char *dollar_word)
{
	if (g_signal == SIGINT)
		structure->last_exit_status = 130;
	replace_words_in_arr(prompt, i, dollar_word,
		ft_itoa(structure->last_exit_status));
	g_signal = 0;
	structure->last_exit_status = 0;
}
