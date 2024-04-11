/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:16:30 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/11 19:14:07 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_cd_command(char **command)
{
	return (ft_strcmp(command[0], "cd") == 0);
}

// void	execute_cd_command(char **command)
void	execute_cd_command(t_info *structure)
{
	char	*path;


	int nb_args;
	nb_args = 0;

	while (structure->table->arr[nb_args])
		nb_args++;

	// printf("The number of arguments is: %d\n", nb_args);





	if (nb_args == 1)
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(structure->table->arr[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			structure->last_exit_status = EXIT_FAILURE;
		}
	}
	else if (nb_args == 2)
	{
		path = structure->table->arr[1];
		if (chdir(path) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(structure->table->arr[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			structure->last_exit_status = EXIT_FAILURE;
		}
	}

	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
	}
	

	
	// if (chdir(path) == -1)
	// {
		
	// 	perror("cd failed");
	// }


	char	*cur_path;
	size_t	size;


	size = PATH_MAX;
	cur_path = getcwd(NULL, size);
	if (cur_path == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	
	
	char *new_string;

	new_string = ft_strjoin("PWD=", cur_path);

	structure->envp = delete_string_array(structure->envp, "PWD");
	structure->envp_export = delete_string_array(structure->envp_export, "PWD");
	add_to_envp(structure, new_string, 1);

	free(new_string);
	
	
	
}
