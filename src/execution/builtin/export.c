/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:50:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 16:45:24 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_export_command(char **command)
{
	return (ft_strcmp(command[0], "export") == 0);
}

static void	export_without_args(t_info *structure)
{
	int		i;
	char 	**envp_sorted;
	int len;
	
	len = 0;
	while (structure->envp_export[len])
		len++;
	envp_sorted = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	while(structure->envp_export[i])
	{
		envp_sorted[i] = ft_strdup(structure->envp_export[i]);
		i++;
	}
	envp_sorted[i] = NULL;
	selectiton_sort_variables(envp_sorted);
	

	int j;
	int number_equal_sign;
	int has_value_env;
	int p;

	p = 0;

	i = 0;
	has_value_env = 0;
	number_equal_sign = 0;
	while (envp_sorted[i])
	{
		int m;
		int count_number_signs;
		m = 0;
		count_number_signs = 0;
		while(envp_sorted[i][m])
		{
			if (envp_sorted[i][m] == '=')
				count_number_signs++;
			m++;
		}

		if (count_number_signs > 0)
		{
			p = 0;
			while(envp_sorted[i][p] && envp_sorted[i][p] != '=')
				p++;
			if (envp_sorted[i][p+1])
				has_value_env = 1;
			else
				has_value_env = 0;
			
			if (has_value_env)
			{
				j = 0;
				int k;
				k = 0;
				while(envp_sorted[i][j])
				{
					k = 0;
					while(envp_sorted[i][k] != '=')
						k++;
					if(envp_sorted[i][k] == '=')
						number_equal_sign = k;
					
					j++;
				}
				
				print_export_structure("declare -x ");
				// char *string_declare;

				// string_declare = "declare -x ";
				j = 0;
				// int l;
				// l = 0;
				// while(string_declare[l])
				// {
				// 	ft_putchar_fd(string_declare[l], 1);
				// 	l++;
				// }
				while(envp_sorted[i][j])
				{
					if (envp_sorted[i][j - 1] == '=' && number_equal_sign == j - 1)
						ft_putchar_fd('\"', 1);
					ft_putchar_fd(envp_sorted[i][j], 1);
					
					if (envp_sorted[i][j + 1] == '\0' && number_equal_sign > 0)
						ft_putchar_fd('\"', 1);
					j++;
				}

				ft_putchar_fd('\n', 1);
			}
			else
			{
				print_export_structure("declare -x ");
				j = 0;
				while(envp_sorted[i][j])
				{
					ft_putchar_fd(envp_sorted[i][j], 1);
					j++;
				}
				ft_putchar_fd('\"', 1);
				ft_putchar_fd('\"', 1);
				ft_putchar_fd('\n', 1);
			}
			

		}
		else
		{
			char *string_declare;

			string_declare = "declare -x ";
			int l;
			l = 0;
			while(string_declare[l])
			{
				ft_putchar_fd(string_declare[l], 1);
				l++;
			}
			j = 0;
			while(envp_sorted[i][j])
			{
				ft_putchar_fd(envp_sorted[i][j], 1);
				j++;
			}
			ft_putchar_fd('\n', 1);
			
			
		}
		
		i++;
	}	
	free_2d_array(envp_sorted);
}

static void	export_with_args(t_info *structure)
{
	int		i;
	int		j;
	int		check_equal_sign;

	check_equal_sign = 0;
	j = 0;
	while (structure->table->arr[1][j])
	{
		if (structure->table->arr[1][j] == '=')
		{
			check_equal_sign++;
			break ;
		}
		j++;
	}
	if (check_equal_sign == 1)
		replace_value_envp(structure, check_equal_sign);
	else
	{
		if (check_env_variable(structure->envp, structure))
			return ;
		else
			add_to_envp(structure, structure->table->arr[1], check_equal_sign);
	}
}

void	execute_export_command(t_info *structure)
{
	if (structure->table->arr[1] == NULL)
		export_without_args(structure);
	else
		export_with_args(structure);
}
