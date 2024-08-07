/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_open_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:32:54 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 20:53:16 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: open_out_fd
 * ---------------------
 * Opens an output file descriptor based on the truncation flag.
 * 
 * table: The command table containing output file information.
 * i: The index of the file in the command table.
 */
static void	open_out_fd(t_cmd *table, int i)
{
	if (table->out.trunc[i])
		table->out.fd = open(table->out.file_name[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		table->out.fd = open(table->out.file_name[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

/* Function: redirec_fd_simple_cmd
 * -------------------------------
 * Redirects the file descriptor for simple commands.
 * 
 * table: The command table containing file descriptor information.
 */
static void	redirec_fd_simple_cmd(t_cmd *table)
{
	if (table->type == SIMPLE_CMD)
	{
		dup2(table->out.fd, STDOUT_FILENO);
		close(table->out.fd);
	}
}

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
	perror(table->out.file_name[i]);
}

/* Function: handle_file
 * ----------------------
 * Opens an output file and handles errors if the file cannot be opened.
 * 
 * table: The command table containing file information.
 * i: The index of the file in the command table.
 * 
 * Returns 1 if successful, 0 if an error occurred.
 */
static int	handle_file(t_cmd *table, int i)
{
	open_out_fd(table, i);
	if (table->out.fd == -1)
	{
		print_error_message(table, i);
		return (0);
	}
	if (close(table->out.fd) == -1)
	{
		print_error_message(table, i);
		return (0);
	}
	return (1);
}

/* Function: open_out_files
 * -------------------------
 * Opens output files for commands, handling multiple files.
 * 
 * table: The command table containing file information.
 * 
 * Returns 1 if all files were successfully opened, 0 if an error occurred.
 */
int	open_out_files(t_cmd *table)
{
	int	i;

	if (table->out.file_name)
	{
		i = 0;
		while (table->out.file_name[i + 1])
		{
			if (!handle_file(table, i))
				return (0);
			i++;
		}
		open_out_fd(table, i);
		if (table->out.fd == -1)
		{
			print_error_message(table, i);
			return (0);
		}
		redirec_fd_simple_cmd(table);
	}
	return (1);
}