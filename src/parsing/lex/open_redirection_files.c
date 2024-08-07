/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection_files.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:25:20 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:20:24 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: open_redirection_files
 * --------------------------------
 * Opens files for input or output redirection based on the tokens provided.
 * 
 * tokens: A linked list of token nodes representing parsed command tokens.
 * 
 * Returns: 1 if all files were successfully opened, 0 otherwise.
 * 
 * This function iterates through the list of tokens. If a token is a redirection
 * token, it checks whether it is for input or output redirection and calls the
 * appropriate function to open the file. If any file cannot be opened, the function
 * returns 0 to indicate failure.
 */
int	open_redirection_files(t_token_node *tokens)
{
	while (tokens)
	{
		if (tokens->token.type == REDIRECTION && tokens->token.in.file_name)
		{
			if (!open_in_red_token(tokens))
				return (0);
		}
		else if (tokens->token.type == REDIRECTION
			&& tokens->token.out.file_name)
		{
			if (!open_out_red_token(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

/* Function: open_in_red_token
 * ---------------------------
 * Opens a file for input redirection.
 * 
 * tokens: The current token node containing the file name for input redirection.
 * 
 * Returns: 1 if the file was successfully opened and closed, 0 otherwise.
 * 
 * This function attempts to open the file specified in the input redirection token
 * for reading. If the file cannot be opened or closed, it prints an error message
 * and returns 0 to indicate failure.
 */
int	open_in_red_token(t_token_node *tokens)
{
	int	i;

	if (tokens->token.in.file_name)
	{
		i = 0;
		while (tokens->token.in.file_name[i])
		{
			tokens->token.in.fd = open(tokens->token.in.file_name[i], O_RDONLY);
			if (tokens->token.in.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.in.file_name[i]);
				return (0);
			}
			if (close(tokens->token.in.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.in.file_name[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

/* Function: open_out_red_token
 * ----------------------------
 * Opens a file for output redirection.
 * 
 * tokens: The current token node containing the file name for output redirection.
 * 
 * Returns: 1 if the file was successfully opened and closed, 0 otherwise.
 * 
 * This function iterates through the file names specified in the output redirection
 * token. For each file, it calls open_based_on_trunc to open the file with the correct
 * flags based on whether the output should be truncated or appended. If any file cannot
 * be opened or closed, it prints an error message and returns 0 to indicate failure.
 */
int	open_out_red_token(t_token_node *tokens)
{
	int	i;

	if (tokens->token.out.file_name)
	{
		i = 0;
		while (tokens->token.out.file_name[i])
		{
			open_based_on_trunc(tokens, i);
			if (tokens->token.out.fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.out.file_name[i]);
				return (0);
			}
			if (close(tokens->token.out.fd) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(tokens->token.out.file_name[i]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

/* Function: open_based_on_trunc
 * -----------------------------
 * Opens a file for output redirection with flags based on truncation preference.
 * 
 * tokens: The current token node containing the file name and truncation preference.
 * i: The index of the file name and truncation preference in the token.
 * 
 * This function opens the file specified in the output redirection token with flags
 * set for either truncation or appending, based on the truncation preference. The file
 * is created if it does not exist, with permissions set to 0644.
 */
void	open_based_on_trunc(t_token_node *tokens, int i)
{
	if (tokens->token.out.trunc[i])
		tokens->token.out.fd = open(tokens->token.out.file_name[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		tokens->token.out.fd = open(tokens->token.out.file_name[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}