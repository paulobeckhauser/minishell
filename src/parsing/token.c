/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/13 15:29:46 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_input_data *input_data)
{
	lexer(input_data);
}

void	lexer(t_input_data *input_data)
{
	t_token_node	*list;
	t_token_node	*root;

	init_needed_data(input_data);
	default_display_with_history(input_data);
	list = init_token_list(input_data);
	if (!list)
		return ;
	root = init_syntax_tree(list);
	print_tree(root, 0, "(ROOT)");
	input_data->input = input_data->start_ptr_save;
	free(input_data->buf);
	free(input_data->input);
}

// Display current directory + prompt for user + addhistory for previous
// prompts, most probably this function will be changed or deleted 
// for sure it will be moved to other file (SZYMON)
void	default_display_with_history(t_input_data *input_data)
{
	input_data->buf = getcwd(NULL, 0);
	if (input_data->buf == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	input_data->buf = ft_strjoin(input_data->buf, "$ ");
	input_data->input = readline(input_data->buf);
	add_history(input_data->input);
}

t_token_node	*init_token_list(t_input_data *input_data)
{
	t_token_node	*node;
	t_token_node	*start_ptr_save;
	t_token_node	*current;
	int				i;

	start_ptr_save = NULL;
	current = NULL;
	i = 0;
	while (1)
	{
		node = malloc(sizeof(t_token_node));
		if (!node)
			return (NULL);
		node->token = init_token_struct(input_data);
		node->next = NULL;
		node->index = i++;
		if (node->token.type == WRONG)
		{
			free(node);
			break ;
		}
		if (!start_ptr_save)
		{
			start_ptr_save = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = current->next;
		}
	}
	return (start_ptr_save);
}

t_token	init_token_struct(t_input_data *input_data)
{
	t_type	type;
	t_token	token;
	t_token	error_token;

	error_token.type = WRONG;
	type = find_token(input_data);
	if (type == PIPE)
	{
		token.type = PIPE;
		token.t_value.single_ptr = "|";
		++input_data->pipe_count;
	}
	else if (type == REDIRECTION)
	{
		token.type = REDIRECTION;
		token.t_value.single_ptr = verify_redirection(input_data);
	}
	else if (type == WORD)
	{
		count_words(input_data);
		init_words_arr(input_data);
		if (!builtin_cmd(input_data->arr[0]))
			token = make_simple_cmd(input_data);
		else
			token = make_builtin_cmd(input_data);
	}
	else
		token = error_token;
	if (type != WORD && type != REDIRECTION)
		input_data->input++;
	return (token);
}

t_type	find_token(t_input_data *input_data)
{
	t_type	type;

	if (input_data->start_ptr_save == NULL)
		input_data->start_ptr_save = input_data->input;
	input_data->word_count = 0;
	skip_whitespaces(input_data);
	if (*input_data->input == 0)
		type = WRONG;
	if (ft_strchr(input_data->symbols, *input_data->input))
	{
		if (*input_data->input == '|' && *(input_data->input + 1) != '|')
			type = PIPE;
		else if (*input_data->input == '<' || *input_data->input == '>')
			type = REDIRECTION;
	}
	else
		type = WORD;
	return (type);
}

void	count_words(t_input_data *input_data)
{
	char	*start_ptr_save;

	start_ptr_save = input_data->input;
	input_data->word_count = 0;
	while (!ft_strchr(input_data->symbols, *input_data->input)
		&& *input_data->input)
	{
		if (ft_strchr(input_data->whitespace, *input_data->input))
		{
			skip_whitespaces(input_data);
			if (*input_data->input)
				input_data->word_count++;
		}
		else
			input_data->input++;
	}
	if (*input_data->input == 0)
		input_data->word_count++;
	input_data->input = start_ptr_save;
}

void	init_words_arr(t_input_data *input_data)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	input_data->arr = malloc((input_data->word_count + 1) * sizeof(char *));
	if (!input_data->arr)
		return ;
	input_data->arr[i] = malloc(get_word_length(input_data) + 1);
	if (!input_data->arr[i])
		return ;
	while (!ft_strchr(input_data->symbols, *input_data->input)
		&& *input_data->input)
	{
		if (ft_strchr(input_data->whitespace, *input_data->input))
		{
			skip_whitespaces(input_data);
			input_data->arr[i][y] = 0;
			if (*input_data->input == 0
				|| ft_strchr(input_data->symbols, *input_data->input))
				break ;
			i++;
			input_data->arr[i] = malloc(get_word_length(input_data) + 1);
			if (!input_data->arr[i])
				return ;
			y = 0;
		}
		else
			input_data->arr[i][y++] = *input_data->input++;
	}
	input_data->arr[i][y] = 0;
	input_data->arr[i + 1] = NULL;
}

t_token	make_simple_cmd(t_input_data *input_data)
{
	t_token	token;

	token.type = SIMPLE_CMD;
	token.t_value.double_ptr = input_data->arr;
	return (token);
}

t_token make_builtin_cmd(t_input_data *input_data)
{
	t_token	token;

	token.type = BUILTIN_CMD;
	token.t_value.double_ptr = input_data->arr;
	return (token);
}

t_token_node	*init_syntax_tree(t_token_node *token)
{
	t_token_node	*last_token;
	t_token_node	*previous_token;

	if (token->token.type == PIPE)
	{
		perror("bash: syntax error near unexpected token `|'");
		return (NULL);
	}
	last_token = NULL;
	previous_token = NULL;
	while (token->next)
	{
		if ((!previous_token || (previous_token && previous_token->token.type != PIPE))
			&& (token->token.type == BUILTIN_CMD || token->token.type == SIMPLE_CMD))
		{
			if (!previous_token)
				token->left = NULL;
			else
				token->left = previous_token;
			token->right = NULL;
			if (!last_token)
				last_token = token;
			previous_token = token;
			token = token->next;
			previous_token->next = NULL;
		}
		else if (token->token.type == PIPE)
		{
			token->left = previous_token;
			if (token->next->token.type == BUILTIN_CMD || token->next->token.type == SIMPLE_CMD)
				token->right = token->next;
			else
				return (NULL);
			if (token->next && token->next->next)
			{
				previous_token = token;
				token = token->next;
				previous_token->next = NULL;
			}
			else
				token->next = NULL;
		}
		else
			token = token->next;
	}
	if (previous_token && previous_token->token.type != PIPE && (token->token.type == BUILTIN_CMD
			|| token->token.type == SIMPLE_CMD))
	{
		if (!previous_token)
			token->left = NULL;
		else
			token->left = previous_token;
		token->right = NULL;
	}
	// else if (token->token.type == PIPE)
	// {
	// 	token->left = previous_token;
	// 	if (token->next && (token->next->token.type == BUILTIN_CMD
	// 		|| token->next->token.type == SIMPLE_CMD))
	// 		token->right = token->next;
	// 	else
	// 		return (NULL);
	// }
	return (token);
}

// t_cmd	*init_tree_node(t_token_node *token_node)
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return (NULL);
// 	if (token_node->token.type != SIMPLE_CMD || token_node->token.type != BUILTIN_CMD)
// 		return (NULL);
// 	cmd->type = token_node->token.type;
// 	cmd->arr = token_node->token.t_value.double_ptr;
// 	cmd->in = STDIN_FILENO;
// 	cmd->out = PIPE;
// 	return (cmd);
// }

void print_tree(t_token_node *node, int depth, char *left_right)
{
    if (node == NULL)
        return;
    // Wypisz wcięcie na podstawie głębokości węzła
    for (int i = 0; i < depth; i++)
        ft_printf("     ");

    // Wypisz informacje o węźle
    ft_printf("%s %s\n", left_right, type_to_string(node->token.type));
    // Przejdź do lewego i prawego dziecka
    print_tree(node->left, depth + 1, "(LEFT)");
	print_tree(node->right, depth + 1, "(RIGHT)");
}

