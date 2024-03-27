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
#include <string.h> //
#include <stddef.h>
#include <stdio.h> //
#include <stdlib.h> //
#include <unistd.h> //
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //
#include <dirent.h>
#include <sys/types.h> //
#include <sys/wait.h> //
#include <stdbool.h>

#define BUFFER_SIZE 128

typedef struct	s_test
{
	int pipefd[2];

	int		term_in;
	int 	term_out;
	char	**input;
	char	**env;
	char	*string;

    int    loc_pipe;
}				t_test	;

///---------------------------------------------------------------------------------------------///
///---------------------------------------------------------------------------------------------///
///---------------------------------------------------------------------------------------------///

int ft_super_countwords(const char *s)
{
    int count = 0;
    int inside_word = 0;
	int i;

	i = 0;
    while (s[i])
    {
        if (s[i] == ' ' && s[i])
            inside_word = 0;
        else if (inside_word == 0)
        {
            inside_word = 1;
            count++;
        }
        i++;
    }
    return (count);
}

const char *ft_skip_spaces(const char *s)
{
    while (*s && *s == ' ')
        s++;
    return s;
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

char *ft_extract_word(const char *s, int size)
{
	int i;
    char *word;

    i = 0;
	word = (char *)malloc((size + 1) * sizeof(char));
	if (!word)
        return NULL;
	while (i < size)
	{
		word[i] = s[i];
		i++;
	}
    word[size] = '\0';
    return (word);
}

char **ft_super_split(char const *s)
{
	int k;
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
			k = 0;
            // Gestion d'erreur : libérer la mémoire allouée précédemment
			while (k < j)
			{
                free(strs[k]);
				k++;				
			}
            free(strs);
            return NULL;
        }
        j++;
        s += word_size;
    }
    strs[j] = NULL;
    return (strs);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + \
		ft_strlen((char *)s2) + 1));
	i = 0;
	if (str != NULL)
	{
		while (*s1 != '\0')
		{
			str[i] = *s1;
			i++;
			s1++;
		}
		while (*s2 != '\0')
		{
			str[i] = *s2;
			i++;
			s2++;
		}
		str[i] = '\0';
	}
	return (str);
}

size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

///---------------------------------------------------------------------------------------------///
///---------------------------------------------------------------------------------------------///
///---------------------------------------------------------------------------------------------///

int	chrcmp(char c, char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (0);
		i++;
	}
	return (1);
}

int	hm_pipe(char *s)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (chrcmp(s[i], "|") == 0)
		{
			count++;
			return (count);
		}
		i++;
	}
	return (-1);
}

int	find_pipe(char *s)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (chrcmp(s[i], "|") == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	tablen_pipe(char **tab)
{
	int i;

	i = 0;
	while (strcmp(tab[i], "|") != 0)
		i++;
	return (i);
}


// Small documentation of the function ft_ultra_split

// tab[k][j][i]

// salut comment ca va | bien et toi

// tab[0][0] == "salut"			ls		|	tmp[0] = "salut"
// tab[0][1] == "comment"		-l		|	tmp[1] = "comment"
// tab[0][2] == "ca"			-a		|	tmp[2] = "ca"
// tab[0][3] == "va"					|	tmp[3] = "va"
// tab[0][4] == NULL (there is a pipe)	|	tmp[4] = "|"

// tab[1][0] == "bien"					|	tmp[5] = "bien"
// tab[1][1] == "et"					|	tmp[6] = "et"
// tab[1][2] == "toi"					|	tmp[7] = "toi"
// tab[1][3] == NULL (end of string)	|	tmp[8] = NULL

char	***ft_ultra_split(char *s)
{
	int i;
	int j;
	int k;
	char **tmp;
	char ***tab;

	i = 0;
	j = 0;
	k = 0;

	if (hm_pipe(s) == -1)
		return (NULL);
	tab = (char ***)malloc(sizeof(char ***) * (hm_pipe(s) + 1));
	if (!tab)
		return (NULL);
	tmp = ft_super_split(s);
	if (!tmp)
		return (NULL);
	while (tmp[i])
	{
		tab[j] = (char **)malloc(sizeof(char *) * (tablen_pipe(tmp) + 1));
		if (!tab[j])
			return (NULL);
		k = 0;
		while (tmp[i] && strcmp(tmp[i], "|") != 0)
		{
			tab[j][k] = strdup(tmp[i]);
			i++;
			k++;
		}
		tab[j][k] = NULL;
		j++;
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

void	ft_loop(char *s)
{
	int i = 0;
	int j = 0;

	char ***tab;
	if (find_pipe(s) == -1)
		return ;
	tab = ft_ultra_split(s);
	if (!tab)
		return ;
	while (tab[i])
	{
		j = 0;
		printf("tab[%d] = \n", i);
		while (tab[i][j])
		{
			printf("|-tab[%d][%d] = %s\n", i, j, tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int main(void)
{
	// int i;
	// char *s;

	// while(1)
	// {
		// i = 0;
		readline("sa");
		// if (s == NULL)
			// break;
		// if (strncmp(s, "exit", 4) == 0)
			// break;
		// ft_loop(s);
		// free(s);
	// }
}

// void	parser(t_base *base)
// {
// 	int i;
	
// 	i = 0;
// 	dup2(base->terminal_in, base->fd_in);
// 	dup2(base->terminal_out, base->fd_out);

// 	dprintf(base->ft_custom_exit, "%s\n", base->input);

// 	if (find_pipe(base->input) == -1)
// 	{
// 		printf("no pipe\n");
// 		get_input_tab(base);
// 		base->tableau[0] = get_exec(base->tableau[0]); // get exec
// 	}
// 	else
// 	{
// 		base->tableau = pre_build_tab(base->input, base);
// 		printf("there is pipe\n");
// 		execute_pipeline(base->tableau,hm_ultra_tab(base->tableau), base);
// 		return ;
// 	}
// 	dprintf(base->ft_custom_exit, "tableau[0][%d] = %s\n", i, base->tableau[0][i]);
// 	dprintf(base->ft_custom_exit, "-------------------------\n");
// 	i = 0;

// 	//get_file_inpout(base, base->tableau[0]); // set in/out

// 	int j = 0;
// 	if (no_command(base->tableau[0]) == 0)
// 	{
// 		while (base->tableau[j])
// 		{
// 			while (base->tableau[0][i])
// 			{
// 				dprintf(base->ft_custom_exit, "-- tableau[%d][%d] = %s\n",j , i, base->tableau[0][i]);
// 				i++;
// 			}
// 			dprintf(base->ft_custom_exit, "-- tableau[%d][%d] = %s\n",j , i, base->tableau[0][i]);
// 			i = 0;
// 			j++;
// 		}
// 		find_command(base, base->tableau[0]);
// 	}
// 	ft_bzero(base->input, ft_strlen(base->input));
// 	dup2(base->terminal_in, base->fd_out);
// 	dup2(base->terminal_out, base->fd_in);
// 	return ;
// }