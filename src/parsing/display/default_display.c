/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:21:39 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:29:19 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* 
 * Function: print_colored_prompt
 * -------------------------------
 * Prints the shell prompt in color and waits for user input.
 * 
 * prompt: A pointer to the t_prompt structure containing prompt information.
 * structure: A pointer to the t_info structure containing shell information.
 * 
 * The function initializes the color for the prompt, handles parent key combinations,
 * and reads the input from the user, freeing the allocated color prompt memory afterwards.
 */
static void	print_colored_prompt(t_prompt *prompt, t_info *structure)
{
    char	*color_prompt;

    color_prompt = init_color_prompt(prompt, structure);
    handle_parent_key_combos();
    prompt->msg = readline(color_prompt);
    free(color_prompt);
}

/* 
 * Function: default_display_with_history
 * --------------------------------------
 * Displays the prompt, handles user input, and manages history.
 * 
 * prompt: A pointer to the t_prompt structure containing prompt information.
 * structure: A pointer to the t_info structure containing shell information.
 * 
 * Returns: 1 if the input is valid and added to history, 0 otherwise.
 * 
 * The function retrieves the current working directory, displays the colored prompt,
 * checks for null input (indicating an exit command), validates quotes in the input,
 * and adds the input to history if valid.
 */
int	default_display_with_history(t_prompt *prompt, t_info *structure)
{
    char	*tmp;

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

/* 
 * Function: init_color_prompt
 * ---------------------------
 * Initializes the color for the shell prompt.
 * 
 * prompt: A pointer to the t_prompt structure containing prompt information.
 * structure: A pointer to the t_info structure containing shell information.
 * 
 * Returns: A pointer to a string containing the colored prompt.
 * 
 * The function constructs the colored prompt based on whether the current folder
 * has been deleted or not, adjusting the shell's working directory and freeing
 * allocated memory as necessary.
 */
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