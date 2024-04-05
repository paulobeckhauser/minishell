/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_structure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:35 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/03 20:19:10 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	print_export_structure(char *str_declare)
{
	int	i;

	i = 0;
	while (str_declare[i])
	{
		ft_putchar_fd(str_declare[i], 1);
		i++;
	}
}

void	print_without_equal_sign(int i, char **envp_sorted,
		char *string_declare)
{
	int	j;

	j = 0;
	while (string_declare[j])
	{
		ft_putchar_fd(string_declare[j], 1);
		j++;
	}
	j = 0;
	while (envp_sorted[i][j])
	{
		ft_putchar_fd(envp_sorted[i][j], 1);
		j++;
	}
	ft_putchar_fd('\n', 1);
}
