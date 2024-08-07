/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:28:31 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 19:32:18 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Function: increment_values
 * ---------------------------
 * Increments the start and count variables by 1.
 * 
 * start: Pointer to the start index, indicating the current position in the array.
 * count: Pointer to the count variable, tracking the number of iterations.
 * 
 * This helper function is used to increment both the start index and the count
 * of processed elements in a loop, simplifying the incrementation process.
 */
static void	increment_values(int *start, int *count)
{
	*start = *start + 1;
	*count = *count + 1;
}

/* Function: replace_string
 * -------------------------
 * Replaces the content of concat_str with temp and frees the old concat_str.
 * 
 * concat_str: The original string to be replaced.
 * temp: The new string to replace concat_str with.
 * 
 * Returns the new string (temp) after freeing the old string (concat_str).
 * This function is used to manage memory efficiently by ensuring that the old
 * string is freed before assigning the new string to the same variable.
 */
static char	*replace_string(char *concat_str, char *temp)
{
	free(concat_str);
	concat_str = ft_strdup(temp);
	free(temp);
	return (concat_str);
}

/* Function: join_string_echo
 * ---------------------------
 * Joins strings from an array starting from a specified index, adding spaces between them.
 * 
 * start: The index in the array from which to start joining strings.
 * structure: A pointer to the main structure containing the command arguments.
 * 
 * Returns a new string that is the result of concatenating all strings from the start index
 * onwards, with spaces inserted between each element. This function is used to construct
 * the output for the echo command, handling the concatenation of multiple arguments into
 * a single string.
 */
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