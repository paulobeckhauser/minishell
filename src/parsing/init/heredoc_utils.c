/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:12:51 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 13:34:50 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: create_tmp_folder
 * ----------------------------
 * Creates a temporary folder named "tmp" to store heredoc temporary files.
 * This function uses fork() to create a child process that executes the mkdir command
 * to create the directory. It waits for the child process to complete before returning.
 */
void	create_tmp_folder(void)
{
    char	**create_tmp_folder;
    pid_t	pid;

    create_tmp_folder = malloc(4 * sizeof(char *));
    if (!create_tmp_folder)
        return ;
    create_tmp_folder[0] = "/bin/mkdir";
    create_tmp_folder[1] = "-p";
    create_tmp_folder[2] = "tmp";
    create_tmp_folder[3] = NULL;
    pid = fork();
    if (pid == 0)
    {
        if (execve(create_tmp_folder[0], create_tmp_folder, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    waitpid(pid, NULL, 0);
    free(create_tmp_folder);
}

/* Function: run_heredoc
 * ---------------------
 * Executes the heredoc functionality for a given token and delimiter.
 * It waits for the user to input the delimiter, saves the input to a temporary file,
 * and then exits.
 * 
 * token: The token associated with the heredoc.
 * delimiter: The delimiter string indicating the end of the heredoc input.
 */
void	run_heredoc(t_token *token, char *delimiter)
{
    char	*heredoc_newline;
    char	*heredoc_msg;

    wait_for_heredoc_delimiter(&heredoc_newline, &heredoc_msg, delimiter);
    open_write_close_tmp_file(token, &heredoc_msg);
    exit(0);
}

/* Function: wait_for_heredoc_delimiter
 * ------------------------------------
 * Waits for the user to input the specified delimiter, collecting all input until then.
 * The input is collected into a dynamically allocated string that is returned via the
 * heredoc_msg parameter.
 * 
 * heredoc_newline: Pointer to store each line of input.
 * heredoc_msg: Pointer to store the concatenated input.
 * delimiter: The delimiter string indicating the end of the heredoc input.
 */
void	wait_for_heredoc_delimiter(char **heredoc_newline, char **heredoc_msg,
    char *delimiter)
{
    char	*tmp;

    tmp = NULL;
    handle_heredoc_key_combos();
    *heredoc_newline = readline("> ");
    if (*heredoc_newline == NULL)
    {
        print_heredoc_end_of_file(delimiter);
        exit(EXIT_SUCCESS);
    }
    *heredoc_msg = ft_calloc(1, 1);
    while (ft_strcmp(*heredoc_newline, delimiter) != 0)
    {
        *heredoc_msg = strjoin_free_both(*heredoc_msg, *heredoc_newline);
        *heredoc_msg = strjoin_free_s1(*heredoc_msg, "\n");
        *heredoc_newline = readline("> ");
        if (*heredoc_newline == NULL)
        {
            print_heredoc_end_of_file(delimiter);
            exit(EXIT_SUCCESS);
        }
    }
    free(*heredoc_newline);
}

/* Function: open_write_close_tmp_file
 * -----------------------------------
 * Opens (or creates if it does not exist) a temporary file named "heredoc_tmp" in the "tmp" directory,
 * writes the collected heredoc input to it, and then closes the file.
 * 
 * token: The token associated with the heredoc, used to store the file descriptor.
 * heredoc_msg: The collected heredoc input to be written to the file.
 */
void	open_write_close_tmp_file(t_token *token, char **heredoc_msg)
{
    token->in.fd = open("tmp/heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (token->in.fd == -1)
    {
        perror("open");
        return ;
    }
    if (*heredoc_msg)
    {
        if (write(token->in.fd, *heredoc_msg, ft_strlen(*heredoc_msg)) == -1)
        {
            perror("write");
            return ;
        }
    }
    if (close(token->in.fd) == -1)
    {
        perror("close");
        return ;
    }
    free(*heredoc_msg);
}