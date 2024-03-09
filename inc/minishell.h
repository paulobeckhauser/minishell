/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:48 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/09 19:31:42 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Made libraries
# include "../libs/libft/inc/ft_printf.h"
# include "../libs/libft/inc/get_next_line.h"
# include "../libs/libft/inc/libft.h"

// Minishell functions libraries
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

// Store variables to handle input (SZYMON)
typedef struct s_input_data
{
	char	*buf;
	char	*input;
	char	*start_ptr_save;
	char	*curr_ptr_save;
	char	*symbols;
	char	*whitespace;
	char	**arr;
	int		word_count;
}	t_input_data;

typedef enum s_type
{
	WRONG = 0,
	PIPE = 1,
	REDIRECTION = 2,
	WORD = 3,
	SIMPLE_COMMAND = 4,
	BUILTIN_COMMAND = 5,
	ARGUMENT = 6,
}	t_type;

typedef struct s_token
{
	t_type	type;
	union u_value
	{
		char	*single_ptr;
		char	**double_ptr;
	} t_value;
	int	output ;
	int input;
	t_token left;
}	t_token;

output = STDOUT_FILENO;
input = STDIN_FILENO;

// token.c
void	lexer(t_input_data *input_data);
void	default_display_with_history(t_input_data *input_data);
void	init_token_struct(t_input_data *input_data);
t_type	find_token(t_input_data *input_data);
char	*verify_redirection(t_input_data *input_data);
void	count_words(t_input_data *input_data);
void	init_words_arr(t_input_data *input_data);
t_token	make_simple_cmd(t_input_data *input_data);

// token_utils.c
void	init_symbols_and_whitespace_strings(t_input_data *input_data);
void	skip_whitespaces(t_input_data *input_data);
int		get_word_length(t_input_data *input_data);
int		builtin_cmd(char *str);
void	free_double_arr(char **arr);

#endif