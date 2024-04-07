/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quote_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:20:23 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/07 14:20:42 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	check_quotes(t_prompt *prompt)
{
	if (count_quotes(prompt) % 2 != 0)
	{
		ft_printf("Error: quotes number not even.\n");
		exit (1);
	}
}

int	count_quotes(t_prompt *prompt)
{
	int		i;
	int		count;
	char	start_quote;

	i = 0;
	count = 0;
	start_quote = 0;
	while (prompt->msg[i])
	{
		if (prompt->msg[i] == '"' || prompt->msg[i] == '\'')
		{
			start_quote = prompt->msg[i];
			i++;
			count++;
			break ;
		}
		i++;
	}
	while (prompt->msg[i])
	{
		if (prompt->msg[i] == start_quote)
			count++;
		i++;
	}
	return (count);
}
