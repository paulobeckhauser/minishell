/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dollar_sign_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:28:23 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 13:00:48 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
		mem_alloc_protection();
	start_ptr_save = word_replacement;
	while (*str)
		*word_replacement++ = *str++;
	*word_replacement = 0;
	word_replacement = start_ptr_save;
	return (word_replacement);
}

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
	if (!info.replacement)
		mem_alloc_protection();
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
