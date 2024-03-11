/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:26:18 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/11 18:01:04 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell.h"

void	init_symbols_and_whitespace_strings(t_input_data *input_data)
{
	input_data->start_ptr_save = NULL;
	input_data->symbols = "|<>";
	input_data->whitespace = " \t\r\n\v";
}

void	skip_whitespaces(t_input_data *input_data)
{
	while (ft_strchr(input_data->whitespace, *input_data->input)
		&& *input_data->input)
		input_data->input++;
}

char	*verify_redirection(t_input_data *input_data)
{
	if (*input_data->input == '<' && *input_data->input != *(input_data->input + 1))
	{
		input_data->input++;
		return ("<");		
	}
	else if (*input_data->input == '>' && *input_data->input != *(input_data->input + 1))
	{
		input_data->input++;
		return (">");
	}
	else if (*input_data->input == '<' && *input_data->input == *(input_data->input + 1))
	{
		input_data->input += 2;
		return ("<<");
	}
	else if (*input_data->input == '>' && *input_data->input == *(input_data->input + 1))
	{
		input_data->input += 2;
		return (">>");
	}
	else
		return (NULL);
}

int	get_word_length(t_input_data *input_data)
{
	int	len;

	len = 0;
	while (!ft_strchr(input_data->symbols, input_data->input[len])
		&& input_data->input[len])
		len++;
	return (len);
}

int	builtin_cmd(char *str)
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

void	free_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

const char	*type_to_string(t_type type)
{
    switch (type) {
        case WRONG: return "WRONG";
        case PIPE: return "PIPE";
        case REDIRECTION: return "REDIRECTION";
        case WORD: return "WORD";
        case SIMPLE_COMMAND: return "SIMPLE_COMMAND";
        case BUILTIN_COMMAND: return "BUILTIN_COMMAND";
        case ARGUMENT: return "ARGUMENT";
        default: return "UNKNOWN";
    }
}