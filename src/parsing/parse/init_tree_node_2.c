/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree_node_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:45:15 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/22 20:45:30 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	join_right_token_to_pipe(t_token_node **token)
{
	if ((*token)->next && ((*token)->next->token.type == BUILTIN_CMD
			|| (*token)->next->token.type == SIMPLE_CMD))
		(*token)->right = (*token)->next;
}
