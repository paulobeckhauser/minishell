/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_with_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:33:28 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:18:47 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	print_export_with_value(int i, char **envp_sorted,
		int number_equal_sign)
{
	int	j;

	j = 0;
	while (envp_sorted[i][j])
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

void	print_with_env_value(int i, char **envp_sorted, t_info *structure)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (envp_sorted[i][j])
	{
		k = 0;
		while (envp_sorted[i][k] != '=')
			k++;
		if (envp_sorted[i][k] == '=')
			structure->number_equal_sign = k;
		j++;
	}
	print_export_structure("declare -x ");
	print_export_with_value(i, envp_sorted, structure->number_equal_sign);
}
