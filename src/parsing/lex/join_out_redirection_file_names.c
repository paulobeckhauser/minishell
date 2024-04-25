/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_out_redirection_file_names.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:16:40 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 12:09:00 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	join_out_redirection_file_names(t_token_node **tokens)
{
	t_vars_join_out_redirect_f_names	vars;

	init_vars_join_out_redirect_f_names(tokens, &vars);
	while (*tokens)
	{
		mark_out_redirection_to_join(tokens, &vars);
		if ((*tokens)->token.type == PIPE || !(*tokens)->next)
		{
			if (vars.i <= 1)
			{
				vars.start_red = NULL;
				vars.i = 0;
				*tokens = (*tokens)->next;
				continue ;
			}
			assign_out_redirect_f_names(&vars);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = vars.head;
}

void	init_vars_join_out_redirect_f_names(t_token_node **tokens,
	t_vars_join_out_redirect_f_names *vars)
{
	vars->last_red = NULL;
	vars->start_red = NULL;
	vars->head = *tokens;
	vars->file_arr = 0;
	vars->i = 0;
}

void	mark_out_redirection_to_join(t_token_node **tokens,
	t_vars_join_out_redirect_f_names *vars)
{
	if ((*tokens)->token.type == REDIRECTION && (*tokens)->token.out.file_name)
	{
		vars->i++;
		if (!vars->start_red)
			vars->start_red = *tokens;
		vars->last_red = *tokens;
	}
}

void	assign_out_redirect_f_names(t_vars_join_out_redirect_f_names *vars)
{
	vars->file_arr = ft_calloc(vars->i + 1, sizeof(char *));
	if (!vars->file_arr)
		mem_alloc_protection();
	vars->last_red_trunc = vars->last_red->token.out.trunc[0];
	free(vars->last_red->token.out.trunc);
	vars->last_red->token.out.trunc = ft_calloc(vars->i, sizeof(int));
	if (!vars->last_red->token.out.trunc)
		mem_alloc_protection();
	vars->file_len = 0;
	vars->y = 0;
	iter_out_redirect_file_names(vars);
	vars->file_arr[vars->y] = NULL;
	vars->last_red->token.out.file_name = vars->file_arr;
	vars->start_red = NULL;
	vars->i = 0;
}

void	iter_out_redirect_file_names(t_vars_join_out_redirect_f_names *vars)
{
	while (vars->start_red && vars->y < vars->i)
	{
		if (vars->start_red->token.type == REDIRECTION
			&& vars->start_red->token.out.file_name)
		{
			vars->file_len = ft_strlen(vars->start_red->token.out.file_name[0]);
			vars->file_arr[vars->y] = malloc(vars->file_len + 1);
			if (!vars->file_arr[vars->y])
				mem_alloc_protection();
			ft_strlcpy(vars->file_arr[vars->y],
				vars->start_red->token.out.file_name[0], vars->file_len + 1);
			free(vars->start_red->token.out.file_name[0]);
			free(vars->start_red->token.out.file_name);
			if (vars->y + 1 == vars->i)
				vars->last_red->token.out.trunc[vars->y++]
					= vars->last_red_trunc;
			else
			{
				vars->last_red->token.out.trunc[vars->y++]
					= vars->start_red->token.out.trunc[0];
				free(vars->start_red->token.out.trunc);
			}
		}
		vars->start_red = vars->start_red->next;
	}
}
