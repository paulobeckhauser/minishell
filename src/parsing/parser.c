/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/05 19:47:58 by sfrankie         ###   ########.fr       */
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
	free_prompt(prompt);
	return (true);
}

t_token_node	*lex(t_info *structure, t_prompt *prompt)
{
	t_token_node	*tokens;

	tokens = init_token_list(structure, prompt);
	if (!tokens)
		return (NULL);
	if (tokens && tokens->token.type == PIPE)
	{
		ft_printf("bash: syntax error near unexpected token `|'\n");
		return (NULL);
	}
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