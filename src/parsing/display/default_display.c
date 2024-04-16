/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/16 16:48:12 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Display current directory + prompt for user + addhistory for previous
// prompts
void	default_display_with_history(t_prompt *prompt, t_info *structure)
{
	char	*color_prompt;
	char	*tmp;
	size_t	size;

	size = PATH_MAX;
	tmp = getcwd(NULL, 0);
	if (tmp)
		prompt->buf = getcwd(NULL, 0);
	else
		structure->folder_deleted = 1;
	free(tmp);
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
		color_prompt = ft_strjoin("\001\033[1;32m\002", structure->folder);
		chdir(structure->folder);
		structure->folder_deleted = 0;
		free(structure->folder);
		
	}
	tmp = ft_strjoin(color_prompt, "\001\033[0m\002");
	free(color_prompt);
	color_prompt = tmp;
	tmp = ft_strjoin(color_prompt, "$> ");
	free(color_prompt);
	color_prompt = tmp;
	return (color_prompt);
}