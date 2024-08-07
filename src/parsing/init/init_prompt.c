/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:24:27 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:35:44 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_prompt
 * ---------------------
 * Initializes the prompt structure with default values.
 * 
 * prompt: A pointer to the t_prompt structure to be initialized.
 * 
 * The function zeroes out the provided t_prompt structure and then initializes
 * it with default values for symbols, whitespace, quotes, and off_symbols.
 * These values are used throughout the shell to parse and interpret user input.
 */
void	init_prompt(t_prompt *prompt)
{
    prompt = ft_memset(prompt, 0, sizeof(t_prompt));
    prompt->symbols = "|<>";
    prompt->whitespace = " \t\r\v";
    prompt->quotes = "\"\'";
    prompt->off_symbols = "!@#$%^&*-+=()[]{}\\|:;,<>/?.";
}