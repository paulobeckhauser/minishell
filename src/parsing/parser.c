/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/15 14:07:19 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parser(t_info *structure, t_prompt *prompt)
{
	t_token_node	*tokens;

	rl_restore_prompt();
	init_prompt(prompt);
	default_display_with_history(prompt, structure);
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
	// if (if_multiple_redirections(tokens))
	// {
		join_redirection_file_names(&tokens);
		delete_repeating_redirection_tokens(&tokens);
	// }
	// if (tokens->next)
	// {
		join_word_tokens(&tokens);
	// }
	if (tokens && tokens->token.type == PIPE)
	{
		ft_printf("bash: syntax error near unexpected token `|'\n");
		return (NULL);
	}
	return (tokens);
}

// int	if_multiple_redirections(t_token_node *tokens)
// {
// 	bool	first;

// 	first = false;
// 	while (tokens)
// 	{
// 		if (tokens->token.type == PIPE)
// 			first = false;
// 		if (tokens->token.type == REDIRECTION)
// 		{
// 			if (!first)
// 				first = true;
// 			else
// 				return (1);
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }

t_cmd	*parse(t_token_node *tokens, t_prompt *prompt)
{
	t_token_node	*tree;
	t_cmd			*table;
	t_cmd			*head;

	tree = init_binary_tree(&tokens);
	head = NULL;
	init_cmd_table(tree, &table, &head, prompt);
	// print_table(head);
	// exit(0);
	return (head);
}
