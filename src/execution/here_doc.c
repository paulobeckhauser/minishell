/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:35:47 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/27 21:06:12 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static int lenght_test_value(t_info *structure, char *input)
// {
//     int lenght_test;

//     ft_strcmp(prompt->heredoc[i],
// }

void here_doc_structure(t_info *structure, t_prompt *prompt)
{
    int i;
    char *input;
    if (prompt->heredoc > 0)
    {
        i = 0;
        while (prompt->heredoc[i])
        {
            // printf("%s\n", prompt->heredoc[i]);
            // ft_printf("heredoc> ");
            while(1)
            {
                // input = get_next_line(STDIN_FILENO);
                input = readline("heredopc>");
                // printf("%s\n", input);
                // if (ft_strcmp(prompt->heredoc[i], input) == 0)
                //     break;
                // printf("%s\n", input);
                // printf("heredopc>");

                free(input);
                
                
            }

            // printf("%d\n", ft_strcmp(prompt->heredoc[i], input ));
            // printf("%s\n", prompt->heredoc[i]);
            i++;
        }
    }
	// {
	// 	char *input;
	// 	int j;
	// 	int lenght_test;

	// 	j = 0;
	// 	while(prompt->heredoc[j])
	// 	{
	// 		input = get_next_line(STDIN_FILENO);

			
			
	// 		j++;
	// 	}
    // }

}