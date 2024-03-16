/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/16 17:59:06 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser(t_cmd *table)
{
	t_input			input;
	t_token_node	*tokens;

	init_input(&input);
	default_display_with_history(&input);
	tokens = lex(&input);
	if (!tokens)
		return ;
	table = parse(tokens, &input);
	if (!table)
		return ;
	print_table(table);
	free_input(&input);
}

t_token_node	*lex(t_input *input)
{
	t_token_node	*tokens;

	tokens = init_token_list(input);
	if (!tokens)
		return (NULL);
	return (tokens);
}

t_cmd	*parse(t_token_node *tokens, t_input *input)
{
	t_token_node	*tree;
	t_cmd			*table;
	t_cmd			*head;
	
	tree = init_binary_tree(&tokens);
	head = NULL;
	init_cmd_table(tree, &table, &head, input);
	return (head);
}
