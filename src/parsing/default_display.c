/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/18 09:37:08 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Display current directory + prompt for user + addhistory for previous
// prompts
void	default_display_with_history(t_input *input)
{
	input->buf = getcwd(NULL, 0);
	if (input->buf == NULL)
	{
		perror("getcwd() error");
		return ;
	}
	//ADDING SOME COLOR JUST TO HELP
	char *color_prompt = ft_strjoin("\001\033[1;32m\002", input->buf);
	color_prompt = ft_strjoin(color_prompt, "\001\033[0m\002");
	color_prompt = ft_strjoin(color_prompt, "$> ");
	input->input = readline(color_prompt);
	//ADDING SOME COLOR JUST TO HELP
	// input->buf = ft_strjoin(input->buf, "$ ");
	// input->input = readline(input->buf);
	add_history(input->input);
}