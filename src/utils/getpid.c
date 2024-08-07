/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:50:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:32:51 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: getpid_from_stat
 * --------------------------
 * Retrieves the process ID of the current process by reading from /proc/self/stat.
 * 
 * prompt: A pointer to the prompt structure containing whitespace characters to be considered.
 * 
 * Returns a string containing the process ID or NULL if an error occurs.
 * 
 * The function opens the /proc/self/stat file to read process information, reads the first line
 * to extract the process ID, allocates memory for the process ID string, and copies the ID into
 * the allocated string. It handles errors such as file opening failure and memory allocation failure.
 * The function ensures to close the file and free allocated resources before returning.
 */
char	*getpid_from_stat(t_prompt *prompt)
{
	char	*file;
	char	*pid_str;
	int		fd;
	int		len;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	file = get_next_line(fd);
	len = 0;
	while (file[len] && !ft_strchr(prompt->whitespace, file[len]))
		len++;
	pid_str = malloc(len + 1);
	if (!pid_str)
		return (free(file), NULL);
	pid_str[len--] = 0;
	while (len >= 0)
	{
		pid_str[len] = file[len];
		len--;
	}
	return (close(fd), free(file), pid_str);
}