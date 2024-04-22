/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/22 19:13:23 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parser(t_info *structure, t_prompt *prompt)
{
	t_token_node	*tokens;

	init_prompt(prompt);
	if (!default_display_with_history(prompt, structure))
		return (false);
	tokens = lex(structure, prompt);
	if (!tokens || if_no_cmd_tokens(tokens))
	{
		free_token_list_full(&tokens);
		free(prompt->start_ptr_save);
		return (false);
	}
	structure->table = parse(tokens, prompt);
	if (!structure->table)
	{
		free(prompt->start_ptr_save);
		return (false);
	}
	free(prompt->start_ptr_save);
	return (true);
}

t_token_node	*lex(t_info *structure, t_prompt *prompt)
{
	t_token_node	*tokens;

	tokens = init_token_list(structure, prompt);
	if (!tokens)
		return (NULL);
	if (if_multiple_redirections(tokens))
	{
		join_redirection_file_names(&tokens);
		delete_repeating_redirection_tokens(&tokens);
	}
	if (if_multiple_word_tokens(tokens))
		join_word_tokens(&tokens);
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

	tree = init_binary_tree(&tokens);
	table = NULL;
	head = NULL;
	init_cmd_table(tree, &table, &head, prompt);
	free_tree(tree);
	return (head);
}
