/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:21:09 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/07 22:23:42 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	if_in_left_redirection(t_token_node **node)
{
	if (((*node)->left->token.t_value.single_ptr[0] == '<'
			&& ft_strlen((*node)->left->token.t_value.single_ptr) == 1)
		|| ((*node)->left->token.t_value.single_ptr[0] == '<'
			&& (*node)->left->token.t_value.single_ptr[1] == '<'))
		return (true);
	return (false);
}

bool	if_in_right_redirection(t_token_node **node)
{
	if (((*node)->right->token.t_value.single_ptr[0] == '<'
			&& ft_strlen((*node)->right->token.t_value.single_ptr) == 1)
		|| ((*node)->right->token.t_value.single_ptr[0] == '<'
			&& (*node)->right->token.t_value.single_ptr[1] == '<'))
		return (true);
	return (false);
}
