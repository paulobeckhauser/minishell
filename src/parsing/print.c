/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:54:34 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/19 20:42:52 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_token_list(t_token_node *node)
{
	if (!node)
		printf("Error: empty token list\n");
	while (node)
	{
		printf("%s\n", type_to_string(node->token.type));
		node = node->next;
	}
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

void	print_table(t_cmd *table)
{
	if (!table)
		printf("Error: empty command table.\n");
	while (table)
	{
		printf("%s\n", type_to_string(table->type));
		table = table->next;
	}
}

void	print_syntax_token_error(t_prompt *prompt)
{
	if (!*prompt->msg)
			ft_printf("bash: syntax error near unexpected token `newline'\n");
	else
		ft_printf("bash: syntax error near unexpected token `%s'\n",
			find_next_token_to_print_in_err(prompt));
}

const char	*type_to_string(t_type type)
{
    switch (type) {
        case END: return "END";
        case PIPE: return "PIPE";
        case REDIRECTION: return "REDIRECTION";
        case WORD: return "WORD";
        case SIMPLE_CMD: return "SIMPLE_CMD";
        case BUILTIN_CMD: return "BUILTIN_CMD";
        case ARGUMENT: return "ARGUMENT";
        default: return "UNKNOWN";
    }
}
