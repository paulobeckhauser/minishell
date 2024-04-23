/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:50:12 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/23 18:50:57 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
