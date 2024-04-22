/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_joined_word_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:45 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/22 19:28:35 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	clean_joined_word_tokens(t_token_node **tokens)
{
	t_token_node	*head;
	t_token_node	*tmp;
	bool			first_cmd;

	head = *tokens;
	tmp = NULL;
	first_cmd = false;
	if ((*tokens)->token.type == BUILTIN_CMD
		|| (*tokens)->token.type == SIMPLE_CMD)
		first_cmd = true;
	while (*tokens)
	{
		if ((*tokens)->token.type == PIPE)
			first_cmd = false;
		if ((*tokens)->next && ((*tokens)->next->token.type == BUILTIN_CMD
				|| (*tokens)->next->token.type == SIMPLE_CMD))
		{
			if (!first_cmd)
				first_cmd = true;
			else
			{
				clean_word_token(tokens, &tmp);
				continue ;
			}
		}
		*tokens = (*tokens)->next;
	}
	*tokens = head;
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
