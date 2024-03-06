/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:24:50 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/19 11:24:54 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "include/minishell.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_super_countwords(const char *s)
{
    int count = 0;
    int inside_word = 0;

    while (*s)
    {
        if (*s == ' ')
            inside_word = 0;
        else if (inside_word == 0)
        {
            inside_word = 1;
            count++;
        }
        s++;
    }
    return count;
}

const char *ft_skip_spaces(const char *s)
{
    while (*s && *s == ' ')
        s++;
    return s;
}

char *ft_extract_word(const char *s, int size)
{
    char *word = (char *)malloc((size + 1) * sizeof(char));
    if (!word)
        return NULL;
    for (int i = 0; i < size; i++)
        word[i] = s[i];
    word[size] = '\0';
    return word;
}

int ft_get_word_size(const char *s)
{
    int size = 0;
    int insidequotes = 0;

    while (s[size])
    {
        if (s[size] == '\"')
            insidequotes = !insidequotes;
        else if (s[size] == ' ' && !insidequotes)
            break;
        size++;
    }
    return size;
}

char **ft_super_split(char const *s)
{
    int j = 0;
    int word_count = ft_super_countwords(s);
    char **strs = (char **)malloc((word_count + 1) * sizeof(char *));
    if (!strs)
        return NULL;

    while (*s && j < word_count)
    {
        s = ft_skip_spaces(s);
        int word_size = ft_get_word_size(s);
        if (j > 0 && *(s - 1) == '=' && word_size == 0)
            word_size++;
        strs[j] = ft_extract_word(s, word_size);
        if (!strs[j])
        {
            // Gestion d'erreur : libérer la mémoire allouée précédemment
            for (int k = 0; k < j; k++)
                free(strs[k]);
            free(strs);
            return NULL;
        }
        j++;
        s += word_size;
    }
    strs[j] = NULL;
    return strs;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == s2[i] && (unsigned char)s1[i] != '\0'
		&& s2[i] != '\0' && i < n - 1)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

int	nb_char(char *s)
{
	int i;
	int j;

	int	count;

	i = 0;
	j = strlen(s);
	j--;
	while ((s[j] == ' ' || s[j] == '\t') && j > 0)
		j--;
	if (j < 0)
		return (-1);
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	count = 0;
	while (i <= j)
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_strndup(char *s, int n)
{
	size_t	len;
	int		i;
	char	*dst;

	len = nb_char((char *)s);
	i = 0;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	while (s[i] && i <= n)
	{
		if (s[i] == ' ' && s[i + 1] == '\0')
			break;
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
//	printf("|%ld|%s|\n",len, dst);
	return (dst);
}


char	**ok_function(char **tab)
{
	int i = 0;
	char **tmp;

	while (tab[i])
		i++;
	if (i < 3)
		return (NULL);
	tmp = malloc(sizeof(char **) * 3);
}

int main(void)
{
	char *str;
	char **tab;
	char **tmp;
	int i = 0;

	while (1)
	{
		i = 0;
		str = readline("file-prog ~$ ");
		tab = ft_super_split(str);
		tmp = ok_function(tab);
		while (tmp[i])
		{
			printf("%s\n", tmp[i]);
			i++;
		}
		free(tmp);
		free(str);
		free(tab);
	}
}

