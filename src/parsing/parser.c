/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:42:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:30:34 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: parser
 * ----------------
 * Parses the user input into a command table.
 * 
 * structure: A pointer to the main data structure.
 * prompt: A pointer to the prompt structure.
 * 
 * Returns true if parsing is successful, false otherwise.
 * 
 * The function initializes the prompt, processes the input with history,
 * tokenizes the input, checks for command tokens, opens redirection files,
 * and parses the tokens into a command table. It cleans up resources if
 * parsing fails at any stage.
 */
bool	parser(t_info *structure, t_prompt *prompt)
{
	t_token_node	*tokens;

	init_prompt(prompt);
	if (!default_display_with_history(prompt, structure))
		return (false);
	tokens = lex(structure, prompt);
	if (!tokens || if_no_cmd_tokens(tokens))
	{
		if (if_no_cmd_tokens(tokens))
		{
			if (!open_redirection_files(tokens))
				structure->last_exit_status = 1;
		}
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

/* Function: lex
 * -------------
 * Tokenizes the input string.
 * 
 * structure: A pointer to the main data structure.
 * prompt: A pointer to the prompt structure.
 * 
 * Returns a pointer to the first token node if successful, NULL otherwise.
 * 
 * The function initializes a token list, checks for multiple redirections,
 * joins file names for redirections, deletes repeating redirection tokens,
 * joins word tokens, and checks for a leading pipe token, indicating a syntax error.
 */
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
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (NULL);
	}
	return (tokens);
}

/* Function: parse
 * ---------------
 * Parses tokens into a command table.
 * 
 * tokens: A pointer to the first token node.
 * prompt: A pointer to the prompt structure.
 * 
 * Returns a pointer to the head of the command table.
 * 
 * The function initializes a binary tree from the tokens, initializes a command
 * table from the tree, and frees the tree.
 */
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