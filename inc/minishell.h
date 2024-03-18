/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:48 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/18 14:14:39 by sfrankie         ###   ########.fr       */
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
# include <stdlib.h>
# include <fcntl.h>

// MACRO variable library
# include <limits.h> // CHECK IF IT IS NOT A PROBLEM TO IMPORT(NORMINETT/ FORBIDDEN FUNCTION)
# include <stdbool.h>

// Store variables to handle input (SZYMON)
typedef struct s_prompt
{
	char	*buf;
	char	*msg;
	char	*start_ptr_save;
	char	*curr_ptr_save;
	char	*symbols;
	char	*whitespace;
	char	**arr;
	int		word_count;
	int		pipe_count;
	int		token_count;
}	t_prompt;

typedef enum s_type
{
	END = 0,
	WRONG_FD = 1,
	PIPE = 2,
	REDIRECTION = 3,
	WORD = 4,
	SIMPLE_CMD = 5,
	BUILTIN_CMD = 6,
	ARGUMENT = 7,
}	t_type;

typedef struct s_cmd
{
	t_type			type;
	char			**arr;
	bool			in_pipe;
	int				in;
	bool			out_pipe;
	int				out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_info
{
    int argc;
	char **argv;
	char **envp; // maybe we don't need to restore, since use only once
    int is_builtin;
    char *path_env;

    char **possible_paths;
    char *path_command;

    t_cmd	*table;
}   t_info;


void store_main_arguments(int argc, char **argv, char **envp, t_info *structure);
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
// int cd(char *path);
// int check_cd_command(char **command);
int is_cd_command(char **command);
void execute_cd_command(char **command);
int is_pwd_command(char **command);
void execute_pwd_command(char **command);
int is_echo_command(char **command);
void    execute_echo_command(char **command, int fd);
int is_export_command(char **command);
void    execute_export_command(char **command, char **envp);
int is_unset_command(char **command);
void    execute_unset_command(char **command);
int is_env_command(char **command);
void    execute_env_command(char **command);
int is_exit_command(char **command);
void    execute_exit_command(char **command);
int ft_setenv(const char *name, const char *value, int overwrite);
int ft_putenv(char *string);




typedef struct s_token
{
	t_type	type;
	int	in;
	int	out;
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

// default_display.c
void			default_display_with_history(t_prompt *prompt);

// free.c
void			free_prompt(t_prompt *prompt);
void			free_double_arr(char **arr);

// init_input.c
void			init_prompt(t_prompt *prompt);

// lex_init_single_token.c lex_init_single_token_2.c
t_token			init_error_token(void);
t_token			init_pipe_token(t_prompt *prompt);
t_token			init_redirection_token(t_prompt *prompt);
t_token			init_cmd_token(t_prompt *prompt);
t_token			init_simple_cmd_token(t_prompt *prompt);
t_token			init_builtin_cmd_token(t_prompt *prompt);

// lex_init_token_list.c
t_token_node	*init_token_list(t_prompt *prompt);
t_token_node	*init_token_node(t_prompt *prompt, int index);
void			add_node_to_list(t_token_node **head, t_token_node **current, t_token_node *new_node);
t_token			init_token_struct(t_prompt *prompt);
t_type			find_token(t_prompt *prompt);

// parser.c
void			parser(t_info *structure);
t_token_node	*lex(t_prompt *prompt);
t_cmd			*parse(t_token_node *tokens, t_prompt *prompt);

// lex_utils.c lex_utils_2.c
char			*verify_redirection(t_prompt *prompt);
void			count_words(t_prompt *prompt);
void			init_words_arr(t_prompt *prompt);
int				if_builtin_cmd(char *str);
void			skip_whitespaces(t_prompt *prompt);
int				get_word_length(t_prompt *prompt);
char			*fetch_file_name(t_prompt *prompt);
char			*find_next_token_to_print_in_err(t_prompt *prompt);

// parse_init_tree_node.c
bool			init_cmd_tree_branch(t_token_node **token, t_token_node **previous_token);
bool			init_pipe_tree_branch(t_token_node **token, t_token_node **previous_token);

// parse_init_cmd_table.c
t_token_node	*init_binary_tree(t_token_node **token_node);
void			init_cmd_table(t_token_node *node, t_cmd **cmd, t_cmd **start_ptr_save, t_prompt *prompt);
t_cmd			*init_cmd(t_token_node *node, t_prompt *prompt);

// print.c
void 			print_tree(t_token_node *node, int depth, char *left_right);
void			print_table(t_cmd *table);
const char		*type_to_string(t_type type);

#endif