/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:48 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/16 14:46:58 by sfrankie         ###   ########.fr       */
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
# include <stdbool.h>

// Store variables to handle input (SZYMON)
typedef struct s_input
{
	char	*buf;
	char	*input;
	char	*start_ptr_save;
	char	*curr_ptr_save;
	char	*symbols;
	char	*whitespace;
	char	**arr;
	int		word_count;
	int		pipe_count;
	int		token_count;
}	t_input;

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
	SIMPLE_CMD = 4,
	BUILTIN_CMD = 5,
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
}	t_token;

typedef struct s_token_node
{
	t_token				token;
	int					index;
	struct s_token_node	*next;
	struct s_token_node	*left;
	struct s_token_node *right;
	
}	t_token_node;

typedef struct s_cmd
{
	t_type			type;
	char			**arr;
	int				in;
	bool			in_pipe;
	int				out;
	bool			out_pipe;
	struct s_cmd	*next;
}	t_cmd;

// default_display.c
void			default_display_with_history(t_input *input);

// free.c
void			free_input(t_input *input);
void			free_double_arr(char **arr);

// init.c
void			init_variables(t_input *input);

// lex_init_token.c lex_init_token_2.c
t_token			init_error_token(void);
t_token			init_pipe_token(t_input *input);
t_token			init_redirection_token(t_input *input);
t_token			init_cmd_token(t_input *input);
t_token			init_simple_cmd_token(t_input *input);
t_token			init_builtin_cmd_token(t_input *input);

// lex_logic.c
t_token_node	*init_token_list(t_input *input);
t_token_node	*init_token_node(t_input *input, int index);
void			add_node_to_list(t_token_node **head, t_token_node **current, t_token_node *new_node);
t_token			init_token_struct(t_input *input);
t_type			find_token(t_input *input);

// parser.c
void			parser(t_input *input);
t_token_node	*lex(t_input *input);
t_cmd			*parse(t_token_node *tokens, t_input *input);

// lex_utils.c lex_utils_2.c
char			*verify_redirection(t_input *input);
void			count_words(t_input *input);
void			init_words_arr(t_input *input);
int				if_builtin_cmd(char *str);
void			skip_whitespaces(t_input *input);
int				get_word_length(t_input *input);

// parse_logic.c
t_token_node	*init_binary_tree(t_token_node *token_node);
void			init_cmd_table(t_token_node *node, t_cmd **cmd, t_cmd **start_ptr_save, t_input *input);
t_cmd			*init_cmd(t_token_node *node, t_input *input);

// print.c
void 			print_tree(t_token_node *node, int depth, char *left_right);
void			print_table(t_cmd *table);
const char		*type_to_string(t_type type);

#endif
