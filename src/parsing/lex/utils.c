/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:57:55 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 12:02:52 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

int	if_builtin_cmd(char *str)
{
	char	**builtins;
	int		i;

	builtins = malloc(8 * sizeof(char *));
	if (!builtins)
		mem_alloc_protection();
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
