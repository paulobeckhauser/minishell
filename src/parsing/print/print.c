/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:54:34 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/15 12:51:55 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	print_syntax_token_error(t_prompt *prompt)
{
	if (!*prompt->msg)
		ft_printf("bash: syntax error near unexpected token `newline'\n");
	else
		ft_printf("bash: syntax error near unexpected token `%s'\n",
			find_next_token_to_print_in_err(prompt));
}

// void	print_token_list(t_token_node *node)
// {
// 	if (!node)
// 		printf("Error: empty token list\n");
// 	while (node)
// 	{
// 		printf("%s ", type_to_string(node->token.type));
// 		int	i = 0;
// 		if ((node->token.type == BUILTIN_CMD || node->token.type == SIMPLE_CMD)
// 			&& node->token.t_value.double_ptr)
// 		{
// 			printf("(\"");
// 			while (node->token.t_value.double_ptr[i])
// 				printf("%s ", node->token.t_value.double_ptr[i++]);
// 			printf("\")");
// 		}
// 		printf("\n");
// 		node = node->next;
// 	}
// }

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
		printf("%s ", type_to_string(table->type));
		int	i = 0;
		while (table->arr[i])
			printf("%s ", table->arr[i++]);
		printf("\n");
		table = table->next;
	}
}

void	print_redirection_file(t_cmd *table)
{
	int i;
	if (!table)
		printf("Error: empty command table.\n");
	while (table)
	{
		printf("%s\n", type_to_string(table->type));
		if (table->in.file_name || table->out.file_name)
		{
			if (table->in.file_name)
			{
				i = 0;
				printf("(R_IN): ");
				while (table->in.file_name[i])
					printf("%s ", table->in.file_name[i++]);
				printf("\n");
			}
			if (table->out.file_name)
			{
				i = 0;
				printf("(R_OUT): ");
				while (table->out.file_name[i])
					printf("%s ", table->out.file_name[i++]);
				printf("\n");
			}
		}
		else
			printf("R: no_redirection\n");
		table = table->next;
	}
}

const char	*type_to_string(t_type type)
{
    switch (type) {
        case END: return "END";
		case ERROR: return "ERROR";
        case PIPE: return "PIPE";
        case REDIRECTION: return "REDIRECTION";
        case WORD: return "WORD";
        case SIMPLE_CMD: return "SIMPLE_CMD";
        case BUILTIN_CMD: return "BUILTIN_CMD";
        default: return "UNKNOWN";
    }
}
