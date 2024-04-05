/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:27:43 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/05 14:54:54 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_echo_command(char **command)
{
	return (ft_strcmp(command[0], "echo") == 0);
}

static char	*join_string_echo(int start, int after, t_info *structure,
		char *string)
{
	int	i;

	// printf("%s\n", structure->table->arr[start]);

	int j;
	int count_dollar_sign;

	j = 0;
	count_dollar_sign = 0;
	while(structure->table->arr[start][j])
	{
		if (structure->table->arr[start][j] == '$')
			count_dollar_sign++;
		j++;
	}
	
	char *str_env;
	char *concat_str;

	concat_str = "";

	if (count_dollar_sign > 0)
	{
		// printf("%d\n", count_dollar_sign);

		while(structure->table->arr[start])
		{
			
			j = 0;
			while(structure->table->arr[start][j])
			{
				if (structure->table->arr[start][j] == '$')
				{
					j++;
					int m;
					int n;
					m = j;
					n = 0;
					while(structure->table->arr[start][m] && structure->table->arr[start][m] != ' ')
					{
						m++;
						n++;
					}

					str_env = malloc((n + 1) * sizeof(char));

					int k;
					int p;

					p = 0;
					k = j;
					while(structure->table->arr[start][k] && structure->table->arr[start][k] != ' ')
					{
						str_env[p] = structure->table->arr[start][k];
						k++;
						p++;
						
					}
					str_env[p] = '\0';
		


					//FIND in env
					char *str_temp;
					char *return_str;
					
					int u = 0;
					while(structure->envp_export[u])
					{
						str_temp = allocate_str_temp(structure, str_temp, u);
						str_temp = save_str_temp(structure, u, str_temp);
						if (ft_strcmp(str_temp, str_env) == 0)
						{
						

							int m;
							m = 0;
							while (structure->envp_export[u][m] && structure->envp_export[u][m] != '=')
							{
								
								m++;
							}
							int l;
							int g;
							g = m + 1;

							l = 0;
							while (structure->envp_export[u][m])
							{
								
								l++;
								m++;
								
							}

							return_str = malloc((l) * sizeof(char));

							int p;
							p = 0;
							while(structure->envp_export[u][g])
							{
								return_str[p] = structure->envp_export[u][g];
								g++;
								p++;
							}
							return_str[p] = '\0';
							
						}
						u++;
					}
				
					concat_str = ft_strjoin(concat_str, return_str);
					concat_str = ft_strjoin(concat_str, " ");
				}
				else
					j++;
			}
			
			start++;
		}
		string = ft_strdup(concat_str);
		
	}






	
	else
	{
		
		string = ft_strdup(structure->table->arr[start]);
		i = after;
		while (structure->table->arr[i])
		{
			string = ft_strjoin(string, " ");
			string = ft_strjoin(string, structure->table->arr[i]);
			i++;
		}
	}
	


	
	return (string);
}

static void	redirection_echo(char *string, t_info *structure)
{
	if (structure->table->out.file_name)
		ft_putstr_fd(string, structure->table->out.fd);
	else
		ft_putstr_fd(string, STDOUT_FILENO);
}

void	execute_echo_command(t_info *structure)
{
	char	*string;
	int		n_flag;

	n_flag = 0;
	if (structure->table->arr[1])
	{
		if (ft_strcmp(structure->table->arr[1], "-n") == 0)
			n_flag = 1;
		if (n_flag)
		{
			if (structure->table->arr[2])
				string = join_string_echo(2, 3, structure, string);
			else
				string = ft_strdup("");
		}
		else
		{
			string = join_string_echo(1, 2, structure, string);
			string = ft_strjoin(string, "\n");
		}
	}
	else
		string = ft_strdup("\n");
	redirection_echo(string, structure);
}
