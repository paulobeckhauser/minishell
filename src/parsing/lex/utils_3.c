/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:27:18 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 17:25:15 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*find_next_token_to_print_in_err(t_prompt *prompt)
{
	t_type	type;

	type = find_token(prompt);
	if (type == PIPE)
		return ("|");
	else if (type == REDIRECTION)
		return (verify_redirection(prompt));
	else
		return (NULL);
}

int	if_wrong_pipe_placement(t_token_node **head, t_token_node **current,
	t_info *structure)
{
	if ((*head && (*head)->token.type == PIPE)
		|| (*current && (*current)->token.type == PIPE))
	{
		structure->last_exit_status = 2;
		free_token_list_full(head);
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}
