/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:53:32 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/10 15:06:38 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	verify_dollar(t_info *structure, t_prompt *prompt)
{
	int						i;
	int						y;
	t_single_quote_checker	*head;

	i = 0;
	head = prompt->checker;
	while (prompt->arr[i] && prompt->checker)
	{
		if (prompt->checker && prompt->checker->index == i
			&& prompt->checker->single_quoted)
		{
			i++;
			prompt->checker = prompt->checker->next;
			continue ;
		}
		while (prompt->arr[i] && ft_strchr(prompt->arr[i], '$'))
			handle_dollar(structure, prompt, prompt->arr[i], &i);
		prompt->checker = prompt->checker->next;
		i++;
	}
	prompt->checker = head;
	// free_single_quote_checker_list(prompt);
}

void	handle_dollar(t_info *structure, t_prompt *prompt, char *str, int *i)
{
	char	*dollar_word;
	char	*word_replacement;

	dollar_word = find_dollar_word(prompt, str);
	if (ft_strcmp(dollar_word, "$") == 0)
	{
		++(*i);
		return ;
	}
	if (ft_strcmp(dollar_word, "?") == 0)
		replace_words_in_arr(prompt, *i, dollar_word,
			ft_itoa(structure->last_exit_status));
	word_replacement = replace_dollar_word(structure, dollar_word);
	if (!word_replacement)
		word_replacement = "";
	replace_words_in_arr(prompt, *i, dollar_word, word_replacement);
}

char	*find_dollar_word(t_prompt *prompt, char *str)
{
	int		len;
	int		i;
	char	*dollar_word;
	char	*dollar_start;

	move_pointer_after_dollar(&str);
	if (!*str || (*str) && ft_strchr(prompt->whitespace, *str))
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
	while (*str)
	{
		if (ft_strchr(prompt->whitespace, *str) || *str == '$')
			break ;
		dollar_word[i++] = *str++;
	}
	dollar_word[i] = 0;
	return (dollar_word);
}

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
