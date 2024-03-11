/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_concat_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:44:55 by pabeckha          #+#    #+#             */
/*   Updated: 2024/03/11 15:26:22 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static void	ft_initiate_vars(size_t *i, int *j, int *s_word)
{
	*i = 0;
	*j = 0;
	*s_word = -1;
}

static int	word_count(const char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*str)
	{
		if (*str != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*str == c)
			x = 0;
		str++;
	}
	return (count);
}

static char	*fill_word(const char *str, int start, int end, char *command)
{
	char	*word;
	int		i;
	int		len_command;
	int		total_size;

	if (command == NULL)
		return (NULL);
	len_command = ft_strlen(command);
	i = 0;
	total_size = end - start + 1 + 1 + len_command;
	word = (char *)ft_calloc(total_size, sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '/';
	i++;
	ft_strlcat(word, command, total_size);
	word[i + len_command] = '\0';
	return (word);
}

char	**split_concat_command(char const *s, char c, char *command)
{
	char	**array;
	size_t	i;
	int		j;
	int		s_word;

	ft_initiate_vars(&i, &j, &s_word);
	array = ft_calloc((word_count(s, c) + 2), sizeof(char *));
	if (!array)
		return (NULL);
	while (i < ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			array[j] = fill_word(s, s_word, i, command);
			check_and_free(array, j);
			s_word = -1;
			j++;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}
