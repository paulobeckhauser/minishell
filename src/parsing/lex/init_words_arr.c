/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_words_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:15:05 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/11 23:42:56 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
