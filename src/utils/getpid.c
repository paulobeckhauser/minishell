/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:50:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/25 12:02:56 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*getpid_from_stat(void)
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
	while (file[len] && !ft_strchr(" \t\r\v", file[len]))
		len++;
	pid_str = malloc(len + 1);
	if (!pid_str)
		mem_alloc_protection();
	pid_str[len--] = 0;
	while (len >= 0)
	{
		pid_str[len] = file[len];
		len--;
	}
	return (close(fd), free(file), pid_str);
}
