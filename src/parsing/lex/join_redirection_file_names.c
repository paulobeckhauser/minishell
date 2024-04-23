/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redirection_file_names.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:20:06 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 19:18:10 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	join_redirection_file_names(t_token_node **tokens)
{
	join_in_redirection_file_names(tokens);
	join_out_redirection_file_names(tokens);
}
