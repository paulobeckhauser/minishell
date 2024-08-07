/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:12:35 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:57:49 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: init_primary_redirection_vars
 * ----------------------------------------
 * Initializes primary redirection variables for a token.
 * 
 * token: Pointer to the token structure to initialize.
 * prompt: Pointer to the prompt structure containing redirection priorities.
 * 
 * This function initializes the input and output file descriptors, file names,
 * heredoc status, validation, and last redirection flag of a token based on the
 * given prompt structure.
 */
void	init_primary_redirection_vars(t_token *token, t_prompt *prompt)
{
	token->in.fd = 0;
	token->in.file_name = NULL;
	token->in.heredoc = false;
	token->out.fd = 1;
	token->out.file_name = NULL;
	token->out.trunc = NULL;
	token->val = verify_redirection(prompt);
	token->last_redirection = false;
}

/* Function: init_in_redirection
 * ------------------------------
 * Initializes input redirection for a token.
 * 
 * token: Pointer to the token structure to initialize.
 * file_name: Name of the file for input redirection.
 * prompt: Pointer to the prompt structure containing redirection priorities.
 * 
 * This function sets up input redirection by allocating memory for the file name,
 * setting the input priority if not already set, and marking the token type as REDIRECTION.
 */
void	init_in_redirection(t_token *token, char *file_name, t_prompt *prompt)
{
	if (!prompt->in_prio && !prompt->out_prio)
		prompt->in_prio = true;
	token->in.heredoc = false;
	token->in.file_name = ft_calloc(2, sizeof(char *));
	if (!token->in.file_name)
		return ;
	token->in.file_name[0] = file_name;
	token->in.file_name[1] = NULL;
	token->type = REDIRECTION;
}

/* Function: init_heredoc_in_redirection
 * -------------------------------------
 * Initializes heredoc input redirection for a token.
 * 
 * token: Pointer to the token structure to initialize.
 * delimiter: Delimiter string indicating the end of heredoc input.
 * 
 * This function prepares a token for heredoc input by creating a temporary folder
 * for heredoc files, setting the heredoc flag, allocating memory for the file name,
 * and running the heredoc in a child process.
 */
void	init_heredoc_in_redirection(t_token *token, char *delimiter)
{
	pid_t	pid;

	create_tmp_folder();
	token->in.heredoc = true;
	token->in.file_name = ft_calloc(2, sizeof(char *));
	token->in.file_name[0] = ft_strdup("tmp/heredoc_tmp");
	token->in.file_name[1] = NULL;
	token->in.fd = 0;
	kill(0, SIGUSR1);
	g_signal = SIGUSR1;
	pid = fork();
	if (pid == 0)
		run_heredoc(token, delimiter);
	token->type = REDIRECTION;
	waitpid(pid, NULL, 0);
	g_signal = 0;
	free(delimiter);
}

/* Function: init_truncate_out_redirection
 * ----------------------------------------
 * Initializes output redirection with truncation for a token.
 * 
 * token: Pointer to the token structure to initialize.
 * file_name: Name of the file for output redirection.
 * prompt: Pointer to the prompt structure containing redirection priorities.
 * 
 * This function sets up output redirection with truncation by allocating memory
 * for the file name, setting the output priority if not already set, and marking
 * the token type as REDIRECTION.
 */
void	init_truncate_out_redirection(t_token *token, char *file_name,
	t_prompt *prompt)
{
	if (!prompt->in_prio && !prompt->out_prio)
		prompt->out_prio = true;
	token->out.file_name = ft_calloc(2, sizeof(char *));
	if (!token->out.file_name)
		return ;
	token->out.file_name[0] = file_name;
	token->out.file_name[1] = NULL;
	token->out.fd = 0;
	token->out.trunc = ft_calloc(1, sizeof(int));
	if (!token->out.trunc)
		return ;
	token->out.trunc[0] = 1;
	token->type = REDIRECTION;
}

/* Function: init_append_out_redirection
 * --------------------------------------
 * Initializes output redirection with append for a token.
 * 
 * token: Pointer to the token structure to initialize.
 * file_name: Name of the file for output redirection.
 * prompt: Pointer to the prompt structure containing redirection priorities.
 * 
 * This function sets up output redirection with append by allocating memory for
 * the file name, setting the output priority if not already set, and marking the
 * token type as REDIRECTION.
 */
void	init_append_out_redirection(t_token *token, char *file_name,
	t_prompt *prompt)
{
	if (!prompt->in_prio && !prompt->out_prio)
		prompt->out_prio = true;
	token->out.file_name = ft_calloc(2, sizeof(char *));
	if (!token->out.file_name)
		return ;
	token->out.file_name[0] = file_name;
	token->out.file_name[1] = NULL;
	token->out.fd = 0;
	token->out.trunc = ft_calloc(1, sizeof(int));
	if (!token->out.trunc)
		return ;
	token->type = REDIRECTION;
}
