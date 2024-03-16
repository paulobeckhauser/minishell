/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:26:18 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 11:10:36 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell.h"

void	init_needed_data(t_input *input)
{
	input->start_ptr_save = NULL;
	input->pipe_count = 0;
	input->symbols = "|<>";
	input->whitespace = " \t\r\n\v";
}

void	skip_whitespaces(t_input *input)
{
	while (ft_strchr(input->whitespace, *input->input)
		&& *input->input)
		input->input++;
}

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

int	get_word_length(t_input *input)
{
	int	len;

	len = 0;
	while (!ft_strchr(input->symbols, input->input[len])
		&& input->input[len])
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
        case SIMPLE_CMD: return "SIMPLE_CMD";
        case BUILTIN_CMD: return "BUILTIN_CMD";
        case ARGUMENT: return "ARGUMENT";
        default: return "UNKNOWN";
    }
}