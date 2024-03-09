/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:48 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/09 16:22:17 by sfrankie         ###   ########.fr       */
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
	PIPE = 0,
	REDIRECTION = 1,
	WORD = 2,
	SIMPLE_COMMAND = 3,
	COMMAND = 4,
	ARGUMENT = 5,
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*value;
}	t_token;

// token.c
void	lexer(t_input_data *input_data);
void	default_display_with_history(t_input_data *input_data);
void	init_token_struct(t_input_data *input_data);
t_type	find_token(t_input_data *input_data);
char	*verify_redirection(t_input_data *input_data);
void	count_words(t_input_data *input_data);
void	init_words_arr(t_input_data *input_data);

// token_utils.c
void	init_symbols_and_whitespace_strings(t_input_data* input_data);
void	skip_whitespaces(t_input_data *input_data);
int		get_word_length(t_input_data *input_data);

#endif