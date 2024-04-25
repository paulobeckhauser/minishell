/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_in_redirection_file_names.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:16:30 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 12:08:46 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	join_in_redirection_file_names(t_token_node **tokens)
{
	t_vars_join_in_redirect_f_names	vars;

	init_vars_join_in_redirect_f_names(tokens, &vars);
	while (*tokens)
	{
		mark_in_redirection_to_join(tokens, &vars);
		if ((*tokens)->token.type == PIPE || !(*tokens)->next)
		{
			if (vars.i <= 1)
			{
				vars.start_red = NULL;
				vars.i = 0;
				*tokens = (*tokens)->next;
				continue ;
			}
			vars.file_arr = ft_calloc(vars.i + 1, sizeof(char *));
			if (!vars.file_arr)
				mem_alloc_protection();
			assign_in_redirect_f_names(&vars);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = vars.head;
}

void	init_vars_join_in_redirect_f_names(t_token_node **tokens,
	t_vars_join_in_redirect_f_names *vars)
{
	vars->start_red = NULL;
	vars->last_red = NULL;
	vars->head = *tokens;
	vars->file_arr = 0;
	vars->i = 0;
}

void	mark_in_redirection_to_join(t_token_node **tokens,
	t_vars_join_in_redirect_f_names *vars)
{
	if ((*tokens)->token.type == REDIRECTION && (*tokens)->token.in.file_name)
	{
		vars->i++;
		if (!vars->start_red)
			vars->start_red = *tokens;
		vars->last_red = *tokens;
	}
}

void	assign_in_redirect_f_names(t_vars_join_in_redirect_f_names *vars)
{
	vars->file_len = 0;
	vars->y = 0;
	iter_in_redirect_file_names(vars);
	vars->file_arr[vars->y] = NULL;
	vars->last_red->token.in.file_name = vars->file_arr;
	vars->start_red = NULL;
	vars->i = 0;
}

void	iter_in_redirect_file_names(t_vars_join_in_redirect_f_names *vars)
{
	while (vars->start_red && vars->y < vars->i)
	{
		if (vars->start_red->token.type == REDIRECTION
			&& vars->start_red->token.in.file_name)
		{
			vars->file_len
				= ft_strlen(vars->start_red->token.in.file_name[0]);
			vars->file_arr[vars->y] = malloc(vars->file_len + 1);
			if (!vars->file_arr[vars->y])
				mem_alloc_protection();
			ft_strlcpy(vars->file_arr[vars->y++],
				vars->start_red->token.in.file_name[0], vars->file_len
				+ 1);
			free_double_arr(vars->start_red->token.in.file_name);
		}
		vars->start_red = vars->start_red->next;
	}
}
