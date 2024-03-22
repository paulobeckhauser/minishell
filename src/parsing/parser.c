/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/22 19:26:12 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parser(t_info *structure)
{
	t_prompt		prompt;
	t_token_node	*tokens;

	init_prompt(&prompt);
	default_display_with_history(&prompt);
	tokens = lex(&prompt);
	if (!tokens)
		return (false);
	structure->table = parse(tokens, &prompt);
	if (!structure->table)
		return (false); 
	free_prompt(&prompt);
	return (true);
}

t_token_node	*lex(t_prompt *prompt)
{
	t_token_node	*tokens;

	tokens = init_token_list(prompt);
	if (!tokens)
		return (NULL);
	return (tokens);
}

t_cmd	*parse(t_token_node *tokens, t_prompt *prompt)
{
	t_token_node	*tree;
	t_cmd			*table;
	t_cmd			*head;

	delete_repeating_redirection_tokens(&tokens);
	tree = init_binary_tree(&tokens);
	head = NULL;
	init_cmd_table(tree, &table, &head, prompt);

	return (head);
}