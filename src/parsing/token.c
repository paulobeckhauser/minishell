/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 11:14:45 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_input *input)
{
	lexer(input);
}

void	lexer(t_input *input)
{
	t_token_node	*list;
	t_token_node	*root;
	t_cmd			*cmd_table;
	t_cmd			*start_ptr_save;

	init_needed_data(input);
	default_display_with_history(input);
	list = init_token_list(input);
	if (!list)
		return ;
	root = init_syntax_tree(list);
	// print_tree(root, 0, "(ROOT)");
	start_ptr_save = NULL;
	init_cmd_table(root, &cmd_table, &start_ptr_save, input);
	// print_cmd_table(start_ptr_save);
	input->input = input->start_ptr_save;
	free(input->buf);
	free(input->input);
}

// Display current directory + prompt for user + addhistory for previous
// prompts, most probably this function will be changed or deleted 
// for sure it will be moved to other file (SZYMON)
void	default_display_with_history(t_input *input)
{
	input->buf = getcwd(NULL, 0);
	if (input->buf == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	input->buf = ft_strjoin(input->buf, "$ ");
	input->input = readline(input->buf);
	add_history(input->input);
}

t_token_node	*init_token_list(t_input *input)
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
		node = ft_calloc(1, sizeof(t_token_node));
		if (!node)
			return (NULL);
		node->token = init_token_struct(input);
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
	input->token_count = i;
	return (start_ptr_save);
}

t_token	init_token_struct(t_input *input)
{
	t_type	type;
	t_token	token;
	t_token	error_token;

	error_token.type = WRONG;
	type = find_token(input);
	if (type == PIPE)
	{
		token.type = PIPE;
		token.t_value.single_ptr = "|";
		++input->pipe_count;
	}
	else if (type == REDIRECTION)
	{
		token.type = REDIRECTION;
		token.t_value.single_ptr = verify_redirection(input);
	}
	else if (type == WORD)
	{
		count_words(input);
		init_words_arr(input);
		if (!builtin_cmd(input->arr[0]))
			token = make_simple_cmd(input);
		else
			token = make_builtin_cmd(input);
	}
	else
		token = error_token;
	if (type != WORD && type != REDIRECTION)
		input->input++;
	return (token);
}

t_type	find_token(t_input *input)
{
	t_type	type;

	if (input->start_ptr_save == NULL)
		input->start_ptr_save = input->input;
	input->word_count = 0;
	skip_whitespaces(input);
	if (*input->input == 0)
		type = WRONG;
	if (ft_strchr(input->symbols, *input->input))
	{
		if (*input->input == '|' && *(input->input + 1) != '|')
			type = PIPE;
		else if (*input->input == '<' || *input->input == '>')
			type = REDIRECTION;
	}
	else
		type = WORD;
	return (type);
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

t_token	make_simple_cmd(t_input *input)
{
	t_token	token;

	token.type = SIMPLE_CMD;
	token.t_value.double_ptr = input->arr;
	return (token);
}

t_token make_builtin_cmd(t_input *input)
{
	t_token	token;

	token.type = BUILTIN_CMD;
	token.t_value.double_ptr = input->arr;
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
			if (token->next && (token->next->token.type == BUILTIN_CMD
				|| token->next->token.type == SIMPLE_CMD))
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
	if ((!previous_token || (previous_token && previous_token->token.type != PIPE))
		&& (token->token.type == BUILTIN_CMD || token->token.type == SIMPLE_CMD))
	{
		if (!previous_token)
			token->left = NULL;
		else
			token->left = previous_token;
		token->right = NULL;
	}
	else if (token->token.type == PIPE && !token->right)
	{
		token->left = previous_token;
		if (token->next && (token->next->token.type == BUILTIN_CMD
			|| token->next->token.type == SIMPLE_CMD))
			token->right = token->next;
		else
			token->right = NULL;
	}
	return (token);
}

void print_tree(t_token_node *node, int depth, char *left_right)
{
    if (node == NULL)
        return;
    for (int i = 0; i < depth; i++)
        ft_printf("     ");
    printf("%s %s\n", left_right, type_to_string(node->token.type));
    print_tree(node->left, depth + 1, "(LEFT)");
	print_tree(node->right, depth + 1, "(RIGHT)");
}

void	init_cmd_table(t_token_node *node, t_cmd **cmd, t_cmd **start_ptr_save, t_input *input)
{
	t_cmd	*new_cmd;

	if (!node)
		return ;
	new_cmd = NULL;
	if (node && !node->left && !node->right)
		*start_ptr_save = init_cmd(node, input);
	if (node && node->left && node->left->right)
		init_cmd_table(node->left, cmd, start_ptr_save, input);
	if (node->token.type != PIPE)
		return ;
	if (node->left->token.type != PIPE)
	{
		new_cmd = init_cmd(node->left, input);
		if (!*start_ptr_save)
			*start_ptr_save = new_cmd;
		if (!*cmd)
			*cmd = new_cmd;
		else
		{
			(*cmd)->next = new_cmd;
			*cmd = (*cmd)->next;
		}
		node->left = NULL;
	}
	new_cmd = init_cmd(node->right, input);
	(*cmd)->next = new_cmd;
	*cmd = (*cmd)->next;
	node->right = NULL;
}

t_cmd	*init_cmd(t_token_node *node, t_input *input)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = node->token.type;
	cmd->arr = node->token.t_value.double_ptr;
	if (node->index != input->token_count - 1 && node->index != 0)
	{
		cmd->in_pipe = true;
		cmd->out_pipe = true;
	}
	else if (node->index == 0 && input->token_count > 0)
	{
		cmd->in = STDIN_FILENO;
		cmd->out_pipe = true;
	}
	else if (node->index == input->token_count - 1 && input->token_count > 0)
	{
		cmd->in_pipe = true;
		cmd->out = STDOUT_FILENO;
	}
	else
	{
		cmd->in = STDIN_FILENO;
		cmd->out = STDOUT_FILENO;
	}
	if (node->index == input->token_count - 1)
		cmd->next = NULL;
	return (cmd);
}

void	print_cmd_table(t_cmd *cmd)
{
	if (!cmd)
		printf("Error: empty command table.\n");
	while (cmd)
	{
		printf("%s\n", type_to_string(cmd->type));
		cmd = cmd->next;
	}
}
