/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:21:09 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/22 21:01:55 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	if_in_left_redirection(t_token_node **node)
{
	if (((*node)->left->token.val[0] == '<'
			&& ft_strlen((*node)->left->token.val) == 1)
		|| ((*node)->left->token.val[0] == '<'
			&& (*node)->left->token.val[1] == '<'))
		return (true);
	return (false);
}

bool	if_in_right_redirection(t_token_node **node)
{
	if (((*node)->right->token.val[0] == '<'
			&& ft_strlen((*node)->right->token.val) == 1)
		|| ((*node)->right->token.val[0] == '<'
			&& (*node)->right->token.val[1] == '<'))
		return (true);
	return (false);
}

void	assign_type_arr_in_out(t_cmd *cmd, t_prompt *prompt, t_token_node *node)
{
	cmd->type = node->token.type;
	cmd->arr = node->token.word_val;
	cmd->in_prio = prompt->in_prio;
	cmd->out_prio = prompt->out_prio;
}
