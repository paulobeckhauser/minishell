/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:13:54 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 15:55:40 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: ft_strcmp
 * --------------------
 * Compares two strings character by character.
 * 
 * s1: The first string to be compared.
 * s2: The second string to be compared.
 * 
 * This function iterates through each character of both strings as long as they are
 * identical and neither of the strings has reached its end. If a difference is found,
 * it returns the difference between the ASCII values of the two characters. If the end
 * of both strings is reached without finding any differences, it returns 0, indicating
 * that the strings are identical.
 * 
 * Return: The difference between the ASCII values of the first pair of characters that
 * differ between the two strings. Returns 0 if the strings are identical.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}