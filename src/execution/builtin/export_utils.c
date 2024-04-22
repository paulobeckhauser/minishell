/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:50:31 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/22 18:34:12 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	handle_equal_signs(t_info *structure)
{
	int	first_equal_sign;
	int	i;

	first_equal_sign = 0;
	i = 0;
	if (structure->count_equal_sign > 1)
	{
		while (structure->table->arr[1][i]
			&& structure->table->arr[1][i] != '=')
		{
			i++;
		}
		if (structure->table->arr[1][i] == '=')
			first_equal_sign = i;
		i = 0;
		while (structure->table->arr[1][i])
		{
			if (i != first_equal_sign && structure->table->arr[1][i] == '=')
				structure->table->arr[1][i] = 2;
			i++;
		}
	}
}

static void	use_print_export_structure(t_info *structure, char **array,
		char *new_string, int check_equal_sign)
{
	structure->envp = delete_string_array(structure->envp, array[0]);
	structure->envp_export = delete_string_array(structure->envp_export,
			array[0]);
	add_to_envp(structure, new_string, check_equal_sign);
	free_2d_array(array);
}

static void	print_if_there_is_arg(char *new_string, char **array,
		t_info *structure, int check_equal_sign)
{
	int	i;

	i = 0;
	while (array[1][i])
	{
		if (array[1][i] == 2)
			array[1][i] = '=';
		i++;
	}
	new_string = ft_strjoin(array[0], "=");
	new_string = ft_strjoin(new_string, array[1]);
	new_string = strjoin_free_s1(new_string, array[1]);
	use_print_export_structure(structure, array, new_string, check_equal_sign);
}

void	replace_value_envp(t_info *structure, int check_equal_sign)
{
	char	**array;
	char	*new_string;

	new_string = NULL;
	count_equal_sign(structure);
	handle_equal_signs(structure);
	array = ft_split(structure->table->arr[1], '=');
	if (array[1])
		print_if_there_is_arg(new_string, array, structure, check_equal_sign);
	else
	{
		new_string = ft_strjoin(array[0], "=");
		use_print_export_structure(structure, array, new_string,
			check_equal_sign);
	}
}
