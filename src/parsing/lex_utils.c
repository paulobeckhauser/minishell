/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:57:55 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/18 14:06:38 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	count_words(t_prompt *prompt)
{
	char	*start_ptr_save;

	start_ptr_save = prompt->msg;
	prompt->word_count = 0;
	while (!ft_strchr(prompt->symbols, *prompt->msg)
		&& *prompt->msg)
	{
		if (ft_strchr(prompt->whitespace, *prompt->msg))
		{
			skip_whitespaces(prompt);
			if (*prompt->msg)
				prompt->word_count++;
		}
		else
			prompt->msg++;
	}
	if (*prompt->msg == 0)
		prompt->word_count++;
	prompt->msg = start_ptr_save;
}

void	init_words_arr(t_prompt *prompt)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	prompt->arr = malloc((prompt->word_count + 1) * sizeof(char *));
	if (!prompt->arr)
		return ;
	prompt->arr[i] = malloc(get_word_length(prompt) + 1);
	if (!prompt->arr[i])
		return ;
	while (!ft_strchr(prompt->symbols, *prompt->msg)
		&& *prompt->msg)
	{
		if (ft_strchr(prompt->whitespace, *prompt->msg))
		{
			skip_whitespaces(prompt);
			prompt->arr[i][y] = 0;
			if (*prompt->msg == 0
				|| ft_strchr(prompt->symbols, *prompt->msg))
				break ;
			i++;
			prompt->arr[i] = malloc(get_word_length(prompt) + 1);
			if (!prompt->arr[i])
				return ;
			y = 0;
		}
		else
			prompt->arr[i][y++] = *prompt->msg++;
	}
	prompt->arr[i][y] = 0;
	prompt->arr[i + 1] = NULL;
}

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
	while (builtins[i])
	{
		if (ft_strncmp(builtins[i], str, ft_strlen(builtins[i])) == 0
			&& ft_strlen(builtins[i]) == ft_strlen(str))
			return (free(builtins), 1);
		i++;
	}
	free(builtins);
	return (0);
}

void	skip_whitespaces(t_prompt *prompt)
{
	while (ft_strchr(prompt->whitespace, *prompt->msg)
		&& *prompt->msg)
		prompt->msg++;
}
