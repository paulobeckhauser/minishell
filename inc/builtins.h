/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:14:47 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/19 12:17:52 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		is_cd_command(char **command);
void	execute_cd_command(t_info *structure);
int		is_pwd_command(char **command);
void	execute_pwd_command(char **command);
int		is_echo_command(char **command);
void	execute_echo_command(t_info *structure);
int		is_export_command(char **command);
void	execute_export_command(t_info *structure);
int		is_unset_command(char **command);
void	execute_unset_command(t_info *structure);
int		is_env_command(char **command);
void	execute_env_command(t_info *structure);
int		is_exit_command(char **command);
void	execute_exit_command(t_info *structure);
void	selectiton_sort_variables(char **envp);
void	add_to_envp(t_info *structure, char *str_add, int check_equal_sign);
void	replace_value_envp(t_info *structure, int check_equal_sign);
int		check_env_variable(t_info *structure);
char	**delete_string_array(char **array, char *str_delete);
void	print_export_structure(char *str_declare);
void	print_export_with_value(int i, char **envp_sorted,
			int number_equal_sign);
void	print_export_without_value(int i, char **envp_sorted);
void	check_has_env_value(int i, char **envp_sorted, t_info *structure);
void	print_with_env_value(int i, char **envp_sorted, t_info *structure);
void	print_without_equal_sign(int i, char **envp_sorted,
			char *string_declare);
void	count_number_equal_signs(int i, char **envp_sorted, t_info *structure);
void	allocate_mem_sort_var(t_info *structure);
void	count_equal_sign(t_info *structure);
char	*allocate_str_temp(t_info *structure, char *str_temp, int i);
char	*save_str_temp(t_info *structure, int i, char *str_temp);
char	*get_parent_folder(char *str);
void	free_exec_variables(t_info *structure);
void	export_without_args(t_info *structure);
void	export_with_args(t_info *structure);
// void echo_n_flag(char *string, t_info *structure);
// char *echo_n_flag(char *string, t_info *structure);
char *echo_n_flag(char *string, t_info *structure, int i);
char	*join_string_echo(int start, t_info *structure);
int flag_string_only_n(char *str);

#endif