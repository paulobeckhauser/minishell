/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:54:34 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 22:57:58 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	print_syntax_token_error(t_prompt *prompt)
{
	if (!*prompt->msg)
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
	else
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			find_next_token_to_print_in_err(prompt));
}

void	print_heredoc_end_of_file(char *delimiter)
{
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file", 1);
	ft_putstr_fd(" (wanted `", 1);
	ft_putstr_fd(delimiter, 1);
	ft_putstr_fd("')\n", 1);
}
