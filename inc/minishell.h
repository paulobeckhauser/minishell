/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:48 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/11 18:34:54 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
# include <sys/wait.h>

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

typedef struct s_info
{
    int argc;
	char **argv;
	char **envp; // maybe we don't need to restore, since use only once
    int is_builtin;
    char *path_env;

    char **possible_paths;
    char *path_command;

    
}   t_info;

void execution(int argc, char *argv[], char *envp[], t_info *structure);
int	ft_strcmp(const char *s1, const char *s2);
void check_builtin(t_info *structure, char *str);
void	get_path_env(t_info *structure);


// split_concat_commands
char	**split_concat_command(char const *s, char c, char *command);
char	**check_and_free(char **array, int j);
void	*ft_free(char **strs, int count);

//free variables
void free_2d_array(char **array);

// BUILTIN FUNCTIONS
int cd(char *path);


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
}	t_token;

typedef struct s_token_node
{
	t_token				token;
	int					index;
	struct s_token_node	*next;
}	t_token_node;


// token.c
void			parser(t_input_data *input_data);
void			lexer(t_input_data *input_data);
void			default_display_with_history(t_input_data *input_data);
t_token_node	*init_token_list(t_input_data *input_data);
t_token			init_token_struct(t_input_data *input_data);
t_type			find_token(t_input_data *input_data);
char			*verify_redirection(t_input_data *input_data);
void			count_words(t_input_data *input_data);
void			init_words_arr(t_input_data *input_data);
t_token			make_simple_cmd(t_input_data *input_data);
t_token			make_builtin_cmd(t_input_data *input_data);

// token_utils.c
void			init_symbols_and_whitespace_strings(t_input_data *input_data);
void			skip_whitespaces(t_input_data *input_data);
int				get_word_length(t_input_data *input_data);
int				builtin_cmd(char *str);
void			free_double_arr(char **arr);
const char		*type_to_string(t_type type);

#endif
