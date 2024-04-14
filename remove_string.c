/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:42:10 by pabeckha          #+#    #+#             */
/*   Updated: 2024/04/13 15:00:09 by pabeckha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}



void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i++] = '\0';
	}
	return (ptr);
}




static void	ft_initiate_vars(size_t *i, int *j, int *s_word)
{
	*i = 0;
	*j = 0;
	*s_word = -1;
}

static int	word_count(const char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*str)
	{
		if (*str != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*str == c)
			x = 0;
		str++;
	}
	return (count);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}


char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	int		j;
	int		s_word;

	ft_initiate_vars(&i, &j, &s_word);
	array = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!array)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			array[j] = fill_word(s, s_word, i);
			if (!(array[j]))
				return (ft_free(array, j));
			s_word = -1;
			j++;
		}
		i++;
	}
	return (array);
}

char	*ft_strdup(const char *s1)
{
	char	*string;
	size_t	i;

	string = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	return (string);
}



char *get_parent_folder(char **arr, char *str)
{
    char *str_path;
    

    int i = 0;

    while (arr[i])
    {
        i++;
    }

    str_path = ft_strjoin("/", arr[i - 1]);

    // printf("%s\n", str_path);
    char *str_new;

    str_new = malloc(ft_strlen(str) - ft_strlen(arr[i - 1]) - ft_strlen("/") + 1);

    int k = ft_strlen(str);



    int rem = k - 1;

    int len_pat = ft_strlen(str_path);
    int rem_2 = len_pat - 1;
    
    while (str[rem] && str_path[rem_2] && str[rem] == str_path[rem_2])
    {

        rem_2--;
        rem--;
    }


    
    int t;

    t = 0;
    
    while (str[t] && t <= rem)
    {
        str_new[t] = str[t];
        t++;
    }
    str_new[t] = '\0';


    return (str_new);
}







int main(void)
{
    char *str = "/home/pabeckha/Documents/42_Projects/minishell/zz";

    char **arr;

    arr = ft_split(str, '/');


    char *new_str;

    new_str = get_parent_folder(arr, str);
    printf("%s\n", new_str);



    
}