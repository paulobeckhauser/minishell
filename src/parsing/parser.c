/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/12 23:19:44 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parser(t_info *structure, t_prompt *prompt)
{
	t_token_node	*tokens;

	init_prompt(prompt);
	default_display_with_history(prompt);
	tokens = lex(structure, prompt);
	if (!tokens || if_no_cmd_tokens(tokens))
		return (false);
	structure->table = parse(tokens, prompt);
	if (!structure->table)
		return (false);
	return (true);
}

t_token_node	*lex(t_info *structure, t_prompt *prompt)
{
	t_token_node	*tokens;

	tokens = init_token_list(structure, prompt);
	if (!tokens)
		return (NULL);
	join_redirection_file_names(&tokens);
	join_word_tokens(&tokens);
	delete_repeating_redirection_tokens(&tokens);
	if (tokens && tokens->token.type == PIPE)
	{
		ft_printf("bash: syntax error near unexpected token `|'\n");
		return (NULL);
	}
	return (tokens);
}

void	join_redirection_file_names(t_token_node **tokens)
{
	t_token_node	*start_redirection;
	t_token_node	*last_redirection;
	t_token_node	*head;
	char			**file_arr;
	int				file_len;
	int				i;
	int				y;

	last_redirection = NULL;
	start_redirection = NULL;
	head = *tokens;
	file_arr = 0;
	i = 0;
	while (*tokens)
	{
		if ((*tokens)->token.type == REDIRECTION)
		{
			i++;
			if (!start_redirection)
				start_redirection = *tokens;
			last_redirection = *tokens;
		}
		if ((*tokens)->token.type == PIPE || !(*tokens)->next)
		{
			if (i <= 1)
			{
				start_redirection = NULL;
				i = 0;
				break ;
			}
			file_arr = ft_calloc(i + 1, sizeof(char *));
			if (!file_arr)
				return ;
			file_len = 0;
			y = 0;
			while (start_redirection && y < i)
			{
				if (start_redirection->token.type == REDIRECTION)
				{
					file_len = ft_strlen(start_redirection->token.in.file_name[0]);
					file_arr[y] = malloc(file_len + 1);
					if (!file_arr[y])
						return ;
					ft_strlcpy(file_arr[y++], start_redirection->token.in.file_name[0], file_len + 1);
				}
				start_redirection = start_redirection->next;
			}
			file_arr[y] = NULL;
			int z = 0;
			while (file_arr[z])
				printf("%s\n", file_arr[z++]);
			last_redirection->token.in.file_name = file_arr;
			start_redirection = NULL;
			i = 0;
		}
		*tokens = (*tokens)->next;
	}
	*tokens = head;
}

t_cmd	*parse(t_token_node *tokens, t_prompt *prompt)
{
	t_token_node	*tree;
	t_cmd			*table;
	t_cmd			*head;

	tree = init_binary_tree(&tokens);
	head = NULL;
	init_cmd_table(tree, &table, &head, prompt);
	print_redirection_file(head);
	print_table(head);
	exit (0);
	return (head);
}
