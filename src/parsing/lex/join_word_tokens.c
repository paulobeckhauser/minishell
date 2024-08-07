/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_word_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:38 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:17:15 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: join_word_tokens
 * ---------------------------
 * Joins word tokens into a single command array for each command.
 * 
 * tokens: A pointer to the head of a linked list of token nodes.
 * 
 * This function iterates through the tokens linked list, identifying command
 * tokens and joining their word values into a single array. This is necessary
 * for handling commands with arguments as a single entity. After joining, it
 * cleans up any temporary structures used during the process.
 */
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

/* Function: init_word_tokens_vars
 * --------------------------------
 * Initializes the variables used in the join_word_tokens function.
 * 
 * vars: A pointer to the struct holding the variables for this operation.
 * tokens: A pointer to the head of a linked list of token nodes.
 * 
 * This function sets up the initial state for the variables used in the
 * process of joining word tokens.
 */
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

/* Function: count_words_in_token
 * -------------------------------
 * Counts the number of words in a token's word value array.
 * 
 * arr: The array of word values in a token.
 * 
 * Returns the count of words in the array.
 */
int	count_words_in_token(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

/* Function: run_word_token_join
 * ------------------------------
 * Joins word tokens into a command array for a single command.
 * 
 * vars: A pointer to the struct holding the variables for this operation.
 * 
 * This function creates a new array to hold all word values for a command,
 * including its arguments, and then frees the original word value arrays.
 */
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
			|| vars->curr_save->token.type == SIMPLE_CMD)
			join_words_to_command(&vars->command,
				vars->curr_save->token.word_val);
		vars->curr_save = vars->curr_save->next;
	}
	free_double_arr(vars->arr_save->token.word_val);
	vars->arr_save->token.word_val = vars->command;
	vars->command_word_count = 0;
}

/* Function: join_words_to_command
 * --------------------------------
 * Joins words into the command array.
 * 
 * arr: A pointer to the array where the joined words will be stored.
 * join: The array of words to join into the command array.
 * 
 * This function iterates through the join array, copying each word into the
 * command array. It ensures that the command array is properly null-terminated.
 */
void	join_words_to_command(char ***arr, char **join)
{
	char	**arr_start_ptr_save;
	char	**arr_temp;
	char	**join_start_ptr_save;
	char	**join_temp;
	int		dst_size;

	arr_start_ptr_save = *arr;
	join_start_ptr_save = join;
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
	*arr_temp = NULL;
	join = join_start_ptr_save;
	*arr = arr_start_ptr_save;
}