/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_in_redirection_file_names.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:16:30 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:12:52 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: join_in_redirection_file_names
 * -----------------------------------------
 * Joins the file names for input redirection tokens into a single array.
 * 
 * tokens: A pointer to the head of a linked list of token nodes.
 * 
 * This function iterates through the tokens linked list and groups file names
 * for input redirection tokens that are meant to be joined. It handles the
 * allocation and assignment of memory for the array of file names.
 */
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
				return ;
			assign_in_redirect_f_names(&vars);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = vars.head;
}

/* Function: init_vars_join_in_redirect_f_names
 * ---------------------------------------------
 * Initializes the variables used in joining input redirection file names.
 * 
 * tokens: A pointer to the head of a linked list of token nodes.
 * vars: A pointer to the struct holding the variables for this operation.
 * 
 * This function initializes the variables used throughout the process of
 * joining input redirection file names, setting up the initial state.
 */
void	init_vars_join_in_redirect_f_names(t_token_node **tokens,
	t_vars_join_in_redirect_f_names *vars)
{
	vars->start_red = NULL;
	vars->last_red = NULL;
	vars->head = *tokens;
	vars->file_arr = 0;
	vars->i = 0;
}

/* Function: mark_in_redirection_to_join
 * --------------------------------------
 * Marks input redirection tokens that should be joined together.
 * 
 * tokens: A pointer to the current token in the linked list.
 * vars: A pointer to the struct holding the variables for this operation.
 * 
 * This function iterates through the tokens and marks the start and end of
 * a sequence of input redirection tokens that should be joined together.
 */
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

/* Function: assign_in_redirect_f_names
 * -------------------------------------
 * Assigns the joined file names to the last input redirection token.
 * 
 * vars: A pointer to the struct holding the variables for this operation.
 * 
 * After joining the file names, this function assigns the resulting array
 * of file names to the last input redirection token in the sequence and
 * resets the variables for the next sequence.
 */
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

/* Function: iter_in_redirect_file_names
 * --------------------------------------
 * Iterates through the marked input redirection tokens to join file names.
 * 
 * vars: A pointer to the struct holding the variables for this operation.
 * 
 * This function iterates from the start to the end of the marked input
 * redirection tokens, joining their file names into a single array.
 */
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
				return ;
			ft_strlcpy(vars->file_arr[vars->y++],
				vars->start_red->token.in.file_name[0], vars->file_len
				+ 1);
			free_double_arr(vars->start_red->token.in.file_name);
		}
		vars->start_red = vars->start_red->next;
	}
}