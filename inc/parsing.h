/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:34:47 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/20 18:22:44 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_init_words_arr_vars
{
	int								i;
	int								j;
	int								word_len;
	char							curr_quote;
}									t_init_words_arr_vars;

typedef struct s_single_quote_checker
{
	int								index;
	bool							single_quoted;
	struct s_single_quote_checker	*next;
}									t_single_quote_checker;

typedef struct s_prompt
{
	char							*buf;
	char							*msg;
	char							*start_ptr_save;
	char							*curr_ptr_save;
	char							*symbols;
	char							*whitespace;
	char							*quotes;
	char							*off_symbols;
	char							**arr;
	int								word_count;
	int								pipe_count;
	int								token_count;
	t_single_quote_checker			*checker;
	int								folder_deleted;
	bool							in_prio;
	bool							out_prio;
}									t_prompt;

typedef enum s_type
{
	END = 0,
	ERROR = 1,
	PIPE = 2,
	REDIRECTION = 3,
	WORD = 4,
	SIMPLE_CMD = 5,
	BUILTIN_CMD = 6,
}									t_type;

typedef struct s_in
{
	bool							heredoc;
	int								fd;
	char							**file_name;
}									t_in;

typedef struct s_out
{
	int								*trunc;
	int								fd;
	char							**file_name;
}									t_out;

typedef struct s_token
{
	t_type							type;
	t_in							in;
	t_out							out;
	char							*val;
	char							**word_val;
	bool							last_redirection;
}									t_token;

typedef struct s_cmd
{
	t_type							type;
	char							**arr;
	t_in							in;
	t_out							out;
	bool							in_prio;
	bool							out_prio;
	struct s_cmd					*next;
}									t_cmd;

#endif