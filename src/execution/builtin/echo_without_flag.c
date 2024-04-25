/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_without_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:08:07 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 12:58:53 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*echo_without_flag(char *string, t_info *structure)
{
	char	*first_backup_string;
	char	*second_backup_string;

	first_backup_string = join_string_echo(1, structure);
	second_backup_string = ft_strjoin(first_backup_string, "\n");
	free(string);
	string = ft_strdup(second_backup_string);
	if (string == NULL)
		mem_alloc_protection();
	free(first_backup_string);
	free(second_backup_string);
	return (string);
}
