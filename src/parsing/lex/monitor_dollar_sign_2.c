/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_dollar_sign_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:28:23 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/10 15:31:25 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

void	replace_words_in_arr(t_prompt *prompt, int i, char *dollar_word,
	char *replacement)
{
	t_dollar_replace_info	info;
	int						y;

	info.prompt = prompt;
	info.i = i;
	info.dollar_word = ft_strjoin("$", dollar_word);
	info.replacement = replacement;
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
	free(before_dollar);
	free(after_dollar);
}
