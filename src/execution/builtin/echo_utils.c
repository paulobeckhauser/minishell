/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:28:31 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 19:32:18 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	increment_values(int *start, int *count)
{
	*start = *start + 1;
	*count = *count + 1;
}

static char	*replace_string(char *concat_str, char *temp)
{
	free(concat_str);
	concat_str = ft_strdup(temp);
	free(temp);
	return (concat_str);
}

char	*join_string_echo(int start, t_info *structure)
{
	char	*concat_str;
	int		count;
	char	*temp;

	concat_str = NULL;
	count = 0;
	temp = NULL;
	while (structure->table->arr[start])
	{
		if (count > 0)
		{
			temp = ft_strjoin(concat_str, " ");
			concat_str = replace_string(concat_str, temp);
		}
		if (count == 0)
			concat_str = ft_strjoin("", structure->table->arr[start]);
		else
		{
			temp = ft_strjoin(concat_str, structure->table->arr[start]);
			concat_str = replace_string(concat_str, temp);
		}
		increment_values(&start, &count);
	}
	return (concat_str);
}
