/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_word_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:38 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/21 16:26:02 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	join_word_tokens(t_token_node **tokens)
{
	t_join_word_tokens_vars	vars;

	init_word_tokens_vars(&vars, tokens);
	while (*tokens)
	{
		if (((*tokens)->token.type == BUILTIN_CMD
				|| (*tokens)->token.type == SIMPLE_CMD))
		{
			if (!vars.first_cmd)
			{
				vars.curr_save = *tokens;
				vars.arr_save = *tokens;
				vars.first_cmd = true;
			}
			vars.command_word_count
				+= count_words_in_token((*tokens)->token.word_val);
		}
		if ((*tokens)->token.type == PIPE || !(*tokens)->next)
			run_word_token_join(&vars);
		*tokens = (*tokens)->next;
	}
	*tokens = vars.head;
	clean_joined_word_tokens(tokens);
}

void	init_word_tokens_vars(t_join_word_tokens_vars *vars,
		t_token_node **tokens)
{
	vars->command = NULL;
	vars->head = *tokens;
	vars->curr_save = NULL;
	vars->arr_save = NULL;
	vars->first_cmd = false;
	vars->command_word_count = 0;
}

int	count_words_in_token(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void	run_word_token_join(t_join_word_tokens_vars *vars)
{
	vars->command = ft_calloc(vars->command_word_count + 1, sizeof(char *));
	if (!vars->command)
		return ;
	vars->first_cmd = false;
	while (vars->curr_save)
	{
		if (vars->curr_save->token.type == PIPE)
			break ;
		else if (vars->curr_save->token.type == BUILTIN_CMD
			|| vars->curr_save->token.type == SIMPLE_CMD)\
				join_words_to_command(&vars->command,
					vars->curr_save->token.word_val);
		vars->curr_save = vars->curr_save->next;
	}
	vars->arr_save->token.word_val = vars->command;
	vars->command_word_count = 0;		
}

void	join_words_to_command(char ***arr, char **join)
{
	char	**start_ptr_save;
	char	**arr_temp;
	char	**join_temp;
	int		dst_size;

	start_ptr_save = *arr;
	arr_temp = *arr;
	join_temp = join;
	while (*arr_temp)
		arr_temp++;
	while (*join_temp)
	{
		dst_size = ft_strlen(*join_temp);
		*arr_temp = malloc(dst_size + 1);
		if (!*arr_temp)
			return ;
		ft_strlcpy(*arr_temp, *join_temp, dst_size + 1);
		join_temp++;
		arr_temp++;
	}
	*join = NULL;
	*arr_temp = NULL;
	*arr = start_ptr_save;
}
