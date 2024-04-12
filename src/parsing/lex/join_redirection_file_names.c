/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redirection_file_names.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:20:06 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/13 01:30:14 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	join_redirection_file_names(t_token_node **tokens)
{
	t_token_node	*start_redirection;
	t_token_node	*last_redirection;
	t_token_node	*head;
	char			**file_arr;
	int				file_len;
	int				i;
	int				y;

	last_redirection = NULL;
	start_redirection = NULL;
	head = *tokens;
	file_arr = 0;
	i = 0;
	while (*tokens)
	{
		if ((*tokens)->token.type == REDIRECTION)
		{
			i++;
			if (!start_redirection)
				start_redirection = *tokens;
			last_redirection = *tokens;
		}
		if ((*tokens)->token.type == PIPE || !(*tokens)->next)
		{
			if (i <= 1)
			{
				start_redirection = NULL;
				i = 0;
				break ;
			}
			file_arr = ft_calloc(i + 1, sizeof(char *));
			if (!file_arr)
				return ;
			file_len = 0;
			y = 0;
			while (start_redirection && y < i)
			{
				if (start_redirection->token.type == REDIRECTION)
				{
					file_len = ft_strlen(start_redirection->token.in.file_name[0]);
					file_arr[y] = malloc(file_len + 1);
					if (!file_arr[y])
						return ;
					ft_strlcpy(file_arr[y++], start_redirection->token.in.file_name[0], file_len + 1);
				}
				start_redirection = start_redirection->next;
			}
			file_arr[y] = NULL;
			last_redirection->token.in.file_name = file_arr;
			start_redirection = NULL;
			i = 0;
		}
		*tokens = (*tokens)->next;
	}
	*tokens = head;
}
