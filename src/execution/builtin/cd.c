/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:16:30 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/11 18:40:28 by pabeckha         ###   ########.fr       */
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

	if (structure->table->arr[1] == NULL)
	{
		path = getenv("HOME");
	}
	else
	{
		path = structure->table->arr[1];
	}

	// printf("%s\n", path);
	
	if (chdir(path) == -1)
	{
		
		perror("cd failed");
	}


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
