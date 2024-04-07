/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_no_cmd_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:05:27 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/07 20:54:17 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	if_no_cmd_tokens(t_token_node *tokens)
{
	while (tokens)
	{
		if (tokens->token.type == BUILTIN_CMD
			|| tokens->token.type == SIMPLE_CMD)
			return (false);
		tokens = tokens->next;
	}
	return (true);
}
