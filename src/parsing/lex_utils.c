/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:57:55 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/02 18:10:13 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_heredoc_arr(t_prompt *prompt, t_token_node *list)
{
	char	**start_ptr_save;

	prompt->heredoc = malloc(prompt->heredoc_count * sizeof(char *));
	if (!prompt->heredoc)
		return ;
	start_ptr_save = prompt->heredoc;
	while (list)
	{
		if (list->token.in.heredoc)
			*prompt->heredoc++ = list->token.in.file_name;
		list = list->next;
	}
	prompt->heredoc = start_ptr_save;
}

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
		prompt->heredoc_count++;
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
	char	curr_quote;

	start_ptr_save = prompt->msg;
	prompt->word_count = 0;
	curr_quote = 0;
	while (*prompt->msg)
	{
		if (ft_strchr(prompt->symbols, *prompt->msg))
			break ;
		else if (ft_strchr(prompt->quotes, *prompt->msg))
		{
			curr_quote = *prompt->msg;
			if (prompt->msg == start_ptr_save || ft_strchr(prompt->symbols, *(prompt->msg - 1))
				|| ft_strchr(prompt->whitespace, *(prompt->msg - 1)))
					prompt->word_count++;
			prompt->msg++;
			while (*prompt->msg && *prompt->msg != curr_quote)
				prompt->msg++;
			prompt->msg++;
		}
		else if (ft_strchr(prompt->whitespace, *prompt->msg))
			skip_whitespaces(prompt);
		else
		{
			if (!*(prompt->msg - 1) || (*(prompt->msg - 1)
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

void	init_words_arr(t_prompt *prompt)
{
	int		i;
	int		j;
	int		word_len;
	char	curr_quote;

	i = 0;
	prompt->arr = malloc((prompt->word_count + 1) * sizeof(char *));
	if (!prompt->arr)
		return ;
	while (*prompt->msg)
	{
		if (ft_strchr(prompt->symbols, *prompt->msg))
			break ;
		else if (ft_strchr(prompt->whitespace, *prompt->msg))
		{
			skip_whitespaces(prompt);
		}
		else
		{
			j = 0;
			word_len = get_word_length(prompt);
			prompt->arr[i] = malloc(word_len + 1);
			if (!prompt->arr[i])
				return ;
			while (*prompt->msg && j < word_len)
			{
				if (ft_strchr(prompt->quotes, *prompt->msg))
				{
					curr_quote = *prompt->msg++;
					while (*prompt->msg && *prompt->msg != curr_quote)
						prompt->arr[i][j++] = *prompt->msg++;
					if (*prompt->msg && *prompt->msg == curr_quote)
						prompt->msg++;
				}
				else if (ft_strchr(prompt->whitespace, *prompt->msg)
					|| ft_strchr(prompt->symbols, *prompt->msg))
						break ;
				else
					prompt->arr[i][j++] = *prompt->msg++;
			}
			prompt->arr[i][j] = 0;
			i++;
		}
	}
	prompt->arr[i] = NULL;
}

bool	if_no_space_quotes(t_prompt *prompt, char quote)
{
	int	i;

	i = 0;
	while (prompt->msg[i] && !ft_strchr(prompt->whitespace, prompt->msg[i]))
	{
		if (prompt->msg[i] == quote)
			return (true);
		i++;
	}
	return (false);
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
