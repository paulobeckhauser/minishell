/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_joined_word_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:45 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 13:10:35 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	init_vars_for_clean_joined_word_tokens(t_token_node **tokens,
	t_vars_clean_joined_word_tokens *vars)
{
	vars->head = *tokens;
	vars->tmp = NULL;
	vars->first_cmd = false;
}

void	clean_joined_word_tokens(t_token_node **tokens)
{
	t_vars_clean_joined_word_tokens	vars;

	init_vars_for_clean_joined_word_tokens(tokens, &vars);
	if ((*tokens)->token.type == BUILTIN_CMD
		|| (*tokens)->token.type == SIMPLE_CMD)
		vars.first_cmd = true;
	while (*tokens)
	{
		if ((*tokens)->token.type == PIPE)
			vars.first_cmd = false;
		if ((*tokens)->next && ((*tokens)->next->token.type == BUILTIN_CMD
				|| (*tokens)->next->token.type == SIMPLE_CMD))
		{
			if (!vars.first_cmd)
				vars.first_cmd = true;
			else
			{
				clean_word_token(tokens, &vars.tmp);
				continue ;
			}
		}
		*tokens = (*tokens)->next;
	}
	*tokens = vars.head;
}

void	clean_word_token(t_token_node **tokens, t_token_node **tmp)
{
	if ((*tokens)->next->next)
	{
		*tmp = (*tokens)->next->next;
		free_double_arr((*tokens)->next->token.word_val);
		free((*tokens)->next);
		(*tokens)->next = *tmp;
	}
	else
	{
		free_double_arr((*tokens)->next->token.word_val);
		free((*tokens)->next);
		(*tokens)->next = NULL;
	}
}
