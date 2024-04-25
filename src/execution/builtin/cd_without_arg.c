/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_without_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:18:02 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/25 12:01:26 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	ret_len_home_if_exists(t_info *structure, int i)
{
	int		j;
	int		count;
	char	*home;

	home = "HOME";
	j = 0;
	count = 0;
	while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
	{
		if (structure->envp_export[i][j] == home[j])
			count++;
		j++;
	}
	return (count);
}

static char	*allocate_mem_string(t_info *structure, int i, int j)
{
	int		m;
	int		l;
	char	*path_home;

	path_home = NULL;
	m = j;
	l = 0;
	while (structure->envp_export[i][m])
	{
		m++;
		l++;
	}
	path_home = ft_calloc(l + 1, sizeof(char));
	if (!path_home)
		mem_alloc_protection();
	return (path_home);
}

static void	go_to_home_folder(t_info *structure, int i)
{
	int		j;
	int		k;
	int		t;
	char	*path_home;

	j = 0;
	path_home = NULL;
	while (structure->envp_export[i][j] && structure->envp_export[i][j] != '=')
		j++;
	j++;
	path_home = allocate_mem_string(structure, i, j);
	k = j;
	t = 0;
	while (structure->envp_export[i][k])
	{
		path_home[t] = structure->envp_export[i][k];
		k++;
		t++;
	}
	path_home[t] = '\0';
	execute_handle_error_cd(path_home, structure);
	free(path_home);
}

static void	check_if_home_exists(int check, int i, t_info *structure)
{
	if (check)
		go_to_home_folder(structure, i);
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		structure->last_exit_status = EXIT_FAILURE;
	}
}

void	cd_wihtout_args(t_info *structure)
{
	int		i;
	int		count;
	char	*home;
	int		len;
	int		check;

	home = "HOME";
	i = 0;
	count = 0;
	len = ft_strlen(home);
	check = 0;
	while (structure->envp_export[i])
	{
		count = ret_len_home_if_exists(structure, i);
		if (count == len)
		{
			check = 1;
			break ;
		}
		i++;
	}
	check_if_home_exists(check, i, structure);
}
