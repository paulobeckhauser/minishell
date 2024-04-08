/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:53:32 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/07 17:58:44 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	verify_dollar(t_info *structure, t_prompt *prompt)
{
	int						i;
	int						y;
	t_single_quote_checker	*head;

	i = 0;
	while (prompt->arr[i] && prompt->checker)
	{
		if (prompt->checker && prompt->checker->index == i
			&& prompt->checker->single_quoted)
		{
			i++;
			prompt->checker = prompt->checker->next;
			continue ;
		}
		while (ft_strchr(prompt->arr[i], '$'))
		{
			handle_dollar(structure, prompt, prompt->arr[i], i);
		}
		prompt->checker = prompt->checker->next;
		i++;
	}
	free_single_quote_checker_list(prompt);
}

void	handle_dollar(t_info *structure, t_prompt *prompt, char *str, int i)
{
	char	*dollar_word;
	char	*word_replacement;

	dollar_word = find_dollar_word(prompt, str);
	word_replacement = replace_dollar_word(structure, dollar_word);
	if (!word_replacement)
		word_replacement = "";
	replace_words_in_arr(prompt, i, dollar_word, word_replacement);
}

char	*find_dollar_word(t_prompt *prompt, char *str)
{
	int		len;
	int		i;
	char	*dollar_word;

	while (*str)
	{
		if (*str++ == '$')
			break ;
	}
	len = 0;
	while (str[len] && ft_strchr(prompt->whitespace, str[len])
		&& str[len] != '$')
		len++;
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

char	*replace_dollar_word(t_info *structure, char *str)
{
	char	*word_replacement;
	char	*str_temp;
	int		i;

	i = 0;
	while (structure->envp_export[i])
	{
		str_temp = allocate_str_temp(structure, str_temp, i);
		str_temp = save_str_temp(structure, i, str_temp);
		if (ft_strcmp(str_temp, str) == 0)
			return (extract_dollar_value(structure->envp_export[i]));
		i++;
	}
	return (NULL);
}

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
