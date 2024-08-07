/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quote_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:20:23 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:30:37 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* 
 * Function: check_quotes
 * ----------------------
 * Checks if the number of quotes in the user input is even.
 * 
 * prompt: A pointer to the t_prompt structure containing user input.
 * 
 * Returns: 1 if the number of quotes is even, 0 otherwise.
 * 
 * This function calls count_quotes to get the total number of quotes in the input.
 * If the number is odd, it prints an error message and returns 0, indicating an error.
 */
int	check_quotes(t_prompt *prompt)
{
    if (count_quotes(prompt) % 2 != 0)
    {
        ft_putstr_fd("minishell: quotes number not even\n", 2);
        return (0);
    }
    return (1);
}

/* 
 * Function: count_quotes
 * ----------------------
 * Counts the number of quotes in the user input.
 * 
 * prompt: A pointer to the t_prompt structure containing user input.
 * 
 * Returns: The total number of quotes in the input.
 * 
 * The function iterates through the input string, counting occurrences of both
 * single (') and double (") quotes. It returns the total count of quotes found.
 */
int	count_quotes(t_prompt *prompt)
{
    int		i;
    int		count;
    char	start_quote;

    i = 0;
    count = 0;
    start_quote = 0;
    while (prompt->msg[i])
    {
        if (prompt->msg[i] == '"' || prompt->msg[i] == '\'')
        {
            start_quote = prompt->msg[i];
            i++;
            count++;
            break ;
        }
        i++;
    }
    while (prompt->msg[i])
    {
        if (prompt->msg[i] == start_quote)
            count++;
        i++;
    }
    return (count);
}