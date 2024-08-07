/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:30:45 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:57:45 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: print_error_message
 * ------------------------------
 * Prints an error message to standard error for a specific file.
 * 
 * table: The command table containing file information.
 * i: The index of the file in the command table.
 */
static void	print_error_message(t_cmd *table, int i)
{
	ft_putstr_fd("minishell: ", 2);
	perror(table->in.file_name[i]);
}

/* Function: redirec_fd_simple_cmd
 * --------------------------------
 * Redirects the file descriptor for simple commands.
 * 
 * table: The command table containing file descriptor information.
 */
static void	redirec_fd_simple_cmd(t_cmd *table)
{
	if (table->in.fd != 0 && table->type == SIMPLE_CMD)
	{
		dup2(table->in.fd, STDIN_FILENO);
		close(table->in.fd);
	}
}

/* Function: handle_file
 * ----------------------
 * Opens a file and handles errors if the file cannot be opened.
 * 
 * table: The command table containing file information.
 * i: The index of the file in the command table.
 * 
 * Returns 1 if successful, 0 if an error occurred.
 */
static int	handle_file(t_cmd *table, int i)
{
	table->in.fd = open(table->in.file_name[i], O_RDONLY);
	if (table->in.fd == -1)
	{
		print_error_message(table, i);
		return (0);
	}
	if (close(table->in.fd) == -1)
	{
		print_error_message(table, i);
		return (0);
	}
	return (1);
}

/* Function: execute_opening
 * --------------------------
 * Opens files for reading, handling heredoc or regular file input.
 * 
 * table: The command table containing file and heredoc information.
 * i: The index of the file in the command table.
 * 
 * Returns 1 if successful, 0 if an error occurred.
 */
static int	execute_opening(t_cmd *table, int i)
{
	if (table->in.heredoc)
	{
		table->in.fd = open("tmp/heredoc_tmp", O_RDONLY);
		if (table->in.fd == -1)
		{
			perror("open failed");
			return (0);
		}
		redirec_fd_simple_cmd(table);
	}
	else
	{
		table->in.fd = open(table->in.file_name[i], O_RDONLY);
		if (table->in.fd == -1)
		{
			print_error_message(table, i);
			return (0);
		}
		redirec_fd_simple_cmd(table);
	}
	return (1);
}

/* Function: open_in_files
 * ------------------------
 * Opens input files for commands, handling multiple files and heredoc.
 * 
 * table: The command table containing file information.
 * 
 * Returns 1 if all files were successfully opened, 0 if an error occurred.
 */
int	open_in_files(t_cmd *table)
{
	int	i;

	if (table->in.file_name)
	{
		i = 0;
		while (table->in.file_name[i + 1])
		{
			if (!handle_file(table, i))
				return (0);
			i++;
		}
		if (!execute_opening(table, i))
			return (0);
	}
	return (1);
}