/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 12:52:09 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	lexer_parser(t_input *input)
{
	t_token_node	*tokens;
	t_cmd			*table;

	init_variables(input);
	default_display_with_history(input);
	tokens = lexer(input);
	table = parser(tokens, input);
	print_table(table);
	free_input(input);
}

t_token_node	*lexer(t_input *input)
{
	t_token_node	*tokens;

	tokens = init_token_list(input);
	if (!tokens)
		return (NULL);
	return (tokens);
}

t_cmd	*parser(t_token_node *tokens, t_input *input)
{
	t_token_node	*tree;
	t_cmd			*table;
	t_cmd			*head;
	
	tree = init_binary_tree(tokens);
	head = NULL;
	init_cmd_table(tree, &table, &head, input);
	return (head);
}