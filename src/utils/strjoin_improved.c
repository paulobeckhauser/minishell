/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_improved.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:58:41 by sfrankie          #+#    #+#             */
/*   Updated: 2024/08/07 15:35:11 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: strjoin_free_s1
 * -------------------------
 * Joins two strings into a new string and frees the first input string.
 * 
 * s1: The first string to join. This string will be freed.
 * s2: The second string to join.
 * 
 * Returns a new string that is the concatenation of s1 and s2. Returns NULL if
 * memory allocation fails.
 * 
 * The function allocates memory for a new string that can hold both s1 and s2,
 * copies s1 followed by s2 into the new string, then frees s1. The new string
 * is null-terminated.
 */
char	*strjoin_free_s1(char *s1, char *s2)
{
	char	*string;
	int		i;
	int		j;

	string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	free(s1);
	return (string);
}

/* Function: strjoin_free_s2
 * -------------------------
 * Joins two strings into a new string and frees the second input string.
 * 
 * s1: The first string to join.
 * s2: The second string to join. This string will be freed.
 * 
 * Returns a new string that is the concatenation of s1 and s2. Returns NULL if
 * memory allocation fails.
 * 
 * Similar to strjoin_free_s1, but instead frees s2 after creating the new
 * concatenated string.
 */
char	*strjoin_free_s2(char *s1, char *s2)
{
	char	*string;
	int		i;
	int		j;

	string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	free(s2);
	return (string);
}

/* Function: strjoin_free_both
 * ---------------------------
 * Joins two strings into a new string and frees both input strings.
 * 
 * s1: The first string to join. This string will be freed.
 * s2: The second string to join. This string will be freed.
 * 
 * Returns a new string that is the concatenation of s1 and s2. Returns NULL if
 * memory allocation fails.
 * 
 * Combines the functionality of strjoin_free_s1 and strjoin_free_s2 by freeing
 * both s1 and s2 after creating the new concatenated string.
 */
char	*strjoin_free_both(char *s1, char *s2)
{
	char	*string;
	int		i;
	int		j;

	string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	free(s1);
	free(s2);
	return (string);
}