/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 22:15:31 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Display current directory + prompt for user + addhistory for previous
// prompts

static void	print_colored_prompt(t_prompt *prompt, t_info *structure)
{
	char	*color_prompt;

	color_prompt = init_color_prompt(prompt, structure);
	handle_parent_key_combos();
	prompt->msg = readline(color_prompt);
	free(color_prompt);
}

int	default_display_with_history(t_prompt *prompt, t_info *structure)
{
	char	*tmp;
	size_t	size;

	size = PATH_MAX;
	tmp = getcwd(NULL, 0);
	if (tmp)
		prompt->buf = getcwd(NULL, 0);
	else
		structure->folder_deleted = 1;
	free(tmp);
	print_colored_prompt(prompt, structure);
	if (prompt->msg == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (!check_quotes(prompt))
	{
		free(prompt->msg);
		structure->last_exit_status = 2;
		return (0);
	}
	add_history(prompt->msg);
	return (1);
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
		free(structure->folder);
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
