/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:08 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/18 19:45:34 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_info
{
	char	**envp;
	char	**envp_export;
	char	**envp_sorted;
	int		is_builtin;
	char	*path_env;
	int		number_commands;
	char	**commands;
	char	**possible_paths;
	char	**path_commands;
	int		**fds_pipes;
	pid_t	*pid;
	int		has_value_envp;
	int		number_equal_sign;
	int		count_number_signs;
	int		count_equal_sign;
	t_cmd	*table;
	int		exit_status;
	int		last_exit_status;
	char	*folder;
	int		folder_deleted;
}			t_info;

void		store_envp(char **envp, t_info *structure);
bool		execution(t_info *structure);
int			ft_strcmp(const char *s1, const char *s2);
void		check_builtin(t_info *structure, char *str);
void		check_path(char *path, char *cmd);
int			get_path_env(t_info *structure);
void		get_number_commands(t_info *structure);
void		store_path_commands(t_info *structure);
void		store_commands(t_info *structure);
void		create_pipes(t_info *structure);
void		create_child_processes(t_info *structure);
void		builtin_execution(t_info *structure);
void		pipes_implementation(t_info *structure);
pid_t		wait_child_processes(t_info *structure, int *status);
void		init_vars(t_info *structure);
void		store_last_path(t_info *structure);
int			open_files(t_cmd *table);
int			open_in_files(t_cmd *table);
int			open_out_files(t_cmd *table);
void		commands_execution(t_info *structure, int i);
void	execute_child_process(t_info *structure, int i);

#endif