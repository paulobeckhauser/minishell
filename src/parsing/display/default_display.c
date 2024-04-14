/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/14 12:01:34 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Display current directory + prompt for user + addhistory for previous
// prompts
void	default_display_with_history(t_prompt *prompt, t_info *structure)
{
	char	*color_prompt;
	size_t	size;
	char	**create_tmp_folder;
	pid_t	pid;
	char cwd[PATH_MAX];

	char *str;
	

	char **temp_arr;
	int i;

	// printf("here 1\n");
	size = PATH_MAX;
	if (getcwd(NULL, 0) != NULL)
	{
		prompt->buf = getcwd(NULL, 0);
	

		
		prompt->folder =  getcwd(NULL, size);
		// printf("The value of structure folder is: %s\n", structure->folder);
		// structure->folder =  getcwd(cwd, sizeof(cwd));
		
		// printf("The value of path is: %s\n", prompt->folder);
		
	}
	else
	{
		// printf("The previous folder was: %s\n", prompt->folder);

		// temp_arr = ft_split(prompt->folder, '\\');

		// i = 0;
		// while (temp_arr[i])
		// {
			
		// 	i++;
		// }
		
		// printf("This is the last element of prev folder: %s\n", temp_arr[i]);
		
		
		// structure->folder = getenv("HOME");

		// str = ft_strdup(structure->folder);
		// free(structure->folder);
		// structure->folder = get_parent_folder(str);
		
		// structure->folder =  getcwd(NULL, size);
		
		

		
		// printf("here\n");
		// printf("The value of structure folder is: %s\n", structure->folder);
		


		structure->folder_deleted = 1;
	}

	color_prompt = init_color_prompt(prompt, structure);
	handle_key_combos();
	prompt->msg = readline(color_prompt);
	free(color_prompt);
	if (prompt->msg == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	check_quotes(prompt);
	add_history(prompt->msg);
}

char	*init_color_prompt(t_prompt *prompt, t_info *structure)
{
	char	*color_prompt;
	char	*tmp;

	
	tmp = NULL;
	if (structure->folder_deleted == 0)
	{
		color_prompt = ft_strjoin("\001\033[1;32m\002", prompt->buf);
		free(prompt->buf);
	}
	else
	{
		// printf("here 3\n");
		color_prompt = ft_strjoin("\001\033[1;32m\002", structure->folder);
		chdir(structure->folder);
		structure->folder_deleted = 0;
		// printf("The color prompt is: %s\n", color_prompt);
		free(structure->folder);
		
	}
		// color_prompt = ft_strjoin("\001\033[1;32m\002", structure->folder);
	tmp = ft_strjoin(color_prompt, "\001\033[0m\002");
	free(color_prompt);
	color_prompt = tmp;
	tmp = ft_strjoin(color_prompt, "$> ");
	free(color_prompt);
	color_prompt = tmp;
	return (color_prompt);
}
