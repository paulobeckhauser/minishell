/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:44:33 by pabeckha          #+#    #+#             */
/*   Updated: 2024/08/07 16:02:28 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Function: store_array
 * ---------------------
 * Copies the environment variables array into a new array.
 * 
 * envp: The original environment variables array.
 * 
 * Returns: A new array containing copies of the original environment variables.
 */
static char	**store_array(char **envp)
{
	int		i;
	char	**array;

	i = 0;
	while (envp[i])
		i++;
	array = (char **)malloc((i + 1) * sizeof(char *));
	if (array == NULL)
	{
		perror("Memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		array[i] = ft_strdup(envp[i]);
		if (array[i] == NULL)
		{
			perror("Memory allocation failed!\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

/* Function: store_envp
 * --------------------
 * Stores the environment variables in the t_info structure.
 * 
 * envp: The environment variables array.
 * structure: A pointer to the t_info structure where the environment variables will be stored.
 */
void	store_envp(char **envp, t_info *structure)
{
	structure->envp = store_array(envp);
	structure->envp_export = store_array(envp);
}