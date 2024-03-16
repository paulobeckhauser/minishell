/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:57:55 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 13:15:27 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*verify_redirection(t_input *input)
{
	if (*input->input == '<' && *input->input != *(input->input + 1))
	{
		input->input++;
		return ("<");		
	}
	else if (*input->input == '>' && *input->input != *(input->input + 1))
	{
		input->input++;
		return (">");
	}
	else if (*input->input == '<' && *input->input == *(input->input + 1))
	{
		input->input += 2;
		return ("<<");
	}
	else if (*input->input == '>' && *input->input == *(input->input + 1))
	{
		input->input += 2;
		return (">>");
	}
	else
		return (NULL);
}

void	count_words(t_input *input)
{
	char	*start_ptr_save;

	start_ptr_save = input->input;
	input->word_count = 0;
	while (!ft_strchr(input->symbols, *input->input)
		&& *input->input)
	{
		if (ft_strchr(input->whitespace, *input->input))
		{
			skip_whitespaces(input);
			if (*input->input)
				input->word_count++;
		}
		else
			input->input++;
	}
	if (*input->input == 0)
		input->word_count++;
	input->input = start_ptr_save;
}

void	init_words_arr(t_input *input)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	input->arr = malloc((input->word_count + 1) * sizeof(char *));
	if (!input->arr)
		return ;
	input->arr[i] = malloc(get_word_length(input) + 1);
	if (!input->arr[i])
		return ;
	while (!ft_strchr(input->symbols, *input->input)
		&& *input->input)
	{
		if (ft_strchr(input->whitespace, *input->input))
		{
			skip_whitespaces(input);
			input->arr[i][y] = 0;
			if (*input->input == 0
				|| ft_strchr(input->symbols, *input->input))
				break ;
			i++;
			input->arr[i] = malloc(get_word_length(input) + 1);
			if (!input->arr[i])
				return ;
			y = 0;
		}
		else
			input->arr[i][y++] = *input->input++;
	}
	input->arr[i][y] = 0;
	input->arr[i + 1] = NULL;
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


t_token	init_simple_cmd_token(t_input *input)
{
	t_token	token;

	token.type = SIMPLE_CMD;
	token.t_value.double_ptr = input->arr;
	return (token);
}
