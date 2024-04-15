/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multiple_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:13:25 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/15 14:21:37 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	if_multiple_redirections(t_token_node *tokens)
{
	bool	first;

	first = false;
	while (tokens)
	{
		if (tokens->token.type == PIPE)
			first = false;
		if (tokens->token.type == REDIRECTION)
		{
			if (!first)
				first = true;
			else
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	if_multiple_word_tokens(t_token_node *tokens)
{
	bool	first;

	first = false;
	while (tokens)
	{
		if (tokens->token.type == PIPE)
			first = false;
		if (tokens->token.type == SIMPLE_CMD || tokens->token.type == BUILTIN_CMD)
		{
			if (!first)
				first = true;
			else
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
