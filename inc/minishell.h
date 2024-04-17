/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:44:48 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/17 18:10:12 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_RESET "\x1b[0m"

// Made libraries
# include "../libs/libft/inc/ft_printf.h"
# include "../libs/libft/inc/get_next_line.h"
# include "../libs/libft/inc/libft.h"

// Minishell functions libraries
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

// MACRO variable library

#ifdef __APPLE__
	# include <limits.h>
#else
	# include <linux/limits.h>
#endif


// CHECK IF IT IS NOT A PROBLEM TO IMPORT(NORMINETT/ FORBIDDEN FUNCTION)
# include <stdbool.h>
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
# include <stdbool.h>
# include <errno.h>

# include "exit_codes.h"
# include <errno.h>

extern int				g_signal;

typedef struct s_token_node
{
	t_token				token;
	int					index;
	struct s_token_node	*next;
	struct s_token_node	*left;
	struct s_token_node	*right;

}						t_token_node;

typedef struct s_join_word_tokens_vars
{
	char				**command;
	t_token_node		*head;
	t_token_node		*curr_save;
	t_token_node		*arr_save;
	bool				first_cmd;
	int					command_word_count;
}						t_join_word_tokens_vars;

typedef struct s_dollar_replace_info
{
	t_prompt			*prompt;
	int					i;
	char				*dollar_word;
	char				*replacement;
}						t_dollar_replace_info;

// split_concat_commands
char					**split_concat(char const *s, char c, char *command);
char					**check_and_free(char **array, int j);
void					*ft_free(char **strs, int count);

// free variables
void					free_2d_array(char **array);
void					free_2d_int_array(int **array);

// SIGNALS (signals.c)
void					handle_execution(int signal);
void					handle_key_combos_execution(void);

// DISPLAY (default_display.c, verify_quote_number.c)
// void					default_display_with_history(t_prompt *prompt);
void					default_display_with_history(t_prompt *prompt,
							t_info *structure);
// char					*init_color_prompt(t_prompt *prompt);
char					*init_color_prompt(t_prompt *prompt, t_info *structure);
void					check_quotes(t_prompt *prompt);
int						count_quotes(t_prompt *prompt);

// FREE (free.c)
void					free_prompt(t_prompt *prompt);
void					free_double_arr(char **arr);
void					free_single_quote_checker_list(t_prompt *prompt);
void					free_token_list(t_token_node **list);
void					free_cmd_table(t_cmd **table);

// INIT (heredoc_utils.c, init_prompt.c, init_redirection.c)
void					create_tmp_folder(void);
void					run_heredoc(t_token *token, char *delimiter);
void					wait_for_heredoc_delimiter(char **heredoc_newline,
							char **heredoc_msg, char *delimiter);
void					open_write_close_tmp_file(t_token *token,
							char **heredoc_msg);
void					init_prompt(t_prompt *prompt);
void					init_primary_redirection_vars(t_token *token,
							t_prompt *prompt);
void					init_in_redirection(t_token *token, char *file_name,
							t_prompt *prompt);
void					init_heredoc_in_redirection(t_token *token,
							char *delimiter);
void					create_tmp_folder(void);
void					init_truncate_out_redirection(t_token *token,
							char *file_name, t_prompt *prompt);
void					init_append_out_redirection(t_token *token,
							char *file_name, t_prompt *prompt);

// LEX (init_token_list.c, init_token_type_2.c, init_token_type.c,
// init_words_arr.c,
// monitor_dollar_sign_2.c, monitor_dollar_sign.c, monitor_single_quote.c,
// utils_2.c, utils.c)
int						if_multiple_redirections(t_token_node *tokens);
int						if_multiple_word_tokens(t_token_node *tokens);
t_token_node			*init_token_list(t_info *structure, t_prompt *prompt);
t_token_node			*init_token_node(t_info *structure, t_prompt *prompt,
							int index);
void					add_node_to_list(t_token_node **head,
							t_token_node **current, t_token_node *new_node);
t_token					init_token_struct(t_info *structure, t_prompt *prompt);
t_type					find_token(t_prompt *prompt);
t_token					init_builtin_cmd_token(t_prompt *prompt);
t_token					init_simple_cmd_token(t_prompt *prompt);
t_token					init_end_token(void);
t_token					init_error_token(void);
t_token					init_pipe_token(t_prompt *prompt);
t_token					init_redirection_token(t_prompt *prompt);
t_token					init_cmd_token(t_info *structure, t_prompt *prompt);
void					init_words_arr(t_prompt *prompt);
void					process_word(t_prompt *prompt, int word_len, int i,
							int *j);
void					join_word_tokens(t_token_node **tokens);
void					init_word_tokens_vars(t_join_word_tokens_vars *vars,
							t_token_node **tokens);
void					join_words_to_command(char ***arr, char **join);
void					clean_joined_word_tokens(t_token_node **tokens);
void					clean_word_token(t_token_node **tokens,
							t_token_node **tmp);
int						count_words_in_token(char **arr);
void					run_word_token_join(t_join_word_tokens_vars *vars);
void					replace_words_in_arr(t_prompt *prompt, int i,
							char *dollar_word, char *replacement);
void					replace_word(t_dollar_replace_info *info, int y);
int						verify_dollar(t_info *structure, t_prompt *prompt);
int						handle_dollar(t_info *structure, t_prompt *prompt,
							char *str, int *i);
char					*find_dollar_word(t_prompt *prompt, char *str);
void					move_pointer_after_dollar(char **str);
void					measure_dollar_word_len(char **str, t_prompt *prompt,
							int *len);
char					*replace_dollar_word(t_info *structure, char *str);
char					*extract_dollar_value(char *str);
void					init_single_quote_checker_list(t_prompt *prompt);
void					update_single_quote_status(t_prompt *prompt, int i);
void					skip_whitespaces(t_prompt *prompt);
int						get_word_length(t_prompt *prompt);
int						count_len_inside_quotes(t_prompt *prompt, int i);
char					*fetch_file_name(t_prompt *prompt);
char					*process_file_name(t_prompt *prompt, char *file_name,
							size_t i);
char					*find_next_token_to_print_in_err(t_prompt *prompt);
char					*verify_redirection(t_prompt *prompt);
void					count_words(t_prompt *prompt);
void					count_words_inside_quotes(t_prompt *prompt,
							char **start_ptr_save);
int						if_builtin_cmd(char *str);
bool					if_no_cmd_tokens(t_token_node *tokens);
t_token_node			*init_binary_tree(t_token_node **token_node);
void					find_first_cmd_token(t_token_node *token,
							t_token_node **head);
void					plant_redirections(t_token_node **token,
							t_token_node **previous_token);
void					delete_redirection_tokens_from_list(t_token_node **token,
							t_token_node **head);
void					plant_cmd(t_token_node **token,
							t_token_node **previous_token);
void					init_cmd_table(t_token_node *node, t_cmd **cmd,
							t_cmd **start_ptr_save, t_prompt *prompt);
void					init_left_leaf(t_token_node **node, t_cmd **table,
							t_cmd **head, t_prompt *prompt);
void					init_right_leaf(t_token_node **node, t_cmd **table,
							t_prompt *prompt);
t_cmd					*init_cmd(t_token_node *node, t_prompt *prompt);
bool					mark_redirection_as_previous(t_token_node **token,
							t_token_node **previous_token);
bool					join_redirection_to_cmd(t_token_node **token,
							t_token_node **previous_token);
bool					join_next_redirection_to_cmd(t_token_node **token,
							t_token_node **previous_token);
bool					mark_cmd_as_previous(t_token_node **token,
							t_token_node **previous_token);
bool					join_cmd_to_pipe(t_token_node **token,
							t_token_node **previous_token);
void					delete_repeating_redirection_tokens(t_token_node **tokens);
void					delete_and_close_not_used_redirections(t_token_node **tokens,
							t_token_node **head, t_token_node **previous_token);
void					mark_last_in_redirection(t_token_node *tokens);
void					mark_last_out_redirection(t_token_node *tokens);
bool					if_in_left_redirection(t_token_node **node);
bool					if_in_right_redirection(t_token_node **node);
void					join_redirection_file_names(t_token_node **tokens);
void					join_in_file_names(t_token_node **tokens);
void					join_out_file_names(t_token_node **tokens);

// parser.c
bool					parser(t_info *structure, t_prompt *prompt);
t_token_node			*lex(t_info *structure, t_prompt *prompt);
t_cmd					*parse(t_token_node *tokens, t_prompt *prompt);

// PRINT (print.c)
void					print_syntax_token_error(t_prompt *prompt);
// void					print_token_list(t_token_node *token);
void					print_tree(t_token_node *node, int depth,
							char *left_right);
void					print_table(t_cmd *table);
void					print_redirection_file(t_cmd *table);
const char				*type_to_string(t_type type);

// SIGNALS (signals.c)
void					handle_signal(int signal);
void					handle_key_combos(void);
void					handle_signal_heredoc(int signal);
void					handle_heredoc_combos(void);

#endif