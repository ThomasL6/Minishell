/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:13:12 by vamologl          #+#    #+#             */
/*   Updated: 2024/01/29 10:13:14 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char    *ft_stringnew(size_t size)
// {
//     char    *str;

//     str = (char *)malloc(sizeof(char *) * (size + 1));
//     if (str == NULL)
//         return (NULL);
//     while (size > 0)
//         str[size--] = '\0';
//     str[0] = '\0';
//     return (str);
// }

// char    *ft_substring(char const *s, unsigned int start, size_t len)
// {
//     size_t	i;
//     size_t	j;
//     char	*str;

//     str = (char *)malloc(sizeof(*s) * (len + 1));
//     if (!str)
// 		return (NULL);
//     i = 0;
//     j = 0;
//     while (s[i])
//     {
//         if (i >= start && j < len)
//         {
//             str[j] = s[i];
//             j++;
//         }
//         i++;
//     }
//     str[j] = 0;
//     return (str);
// }





// char    **ft_separ(char *s, char c)
// {
//     int        i;
//     int        j;
//     int        size;
//     int        word;
//     char    **strs;

//     i = 0;
//     j = -1;
//     word = ft_nbrword(s, c);
//     strs = (char **)malloc((word + 1) * sizeof(char *));
//     if (!strs)
//         return (NULL);
//     while (++j < word)
//     {
//         while (s[i] == c)
//             i++;
//         size = mesure_word(s, c, i);
//         strs[j] = ft_substring(s, i, size);
//         if (!strs[j])
//             return (NULL);
//         i += size;
//     }
//     strs[j] = NULL;
//     free(s);
//     return (strs);
// }


// int	nb_word(char *s) // backup
// {
// 	int	len;
// 	int	tmp;
// 	int	i;

// 	len = 0;
// 	tmp = 0;
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == 1)
// 		{
// 			len++;
// 			while (s[i] != 1 && s[i] != '\0')
// 				i++;
// 			if (s[i] != 1 && s[i + 1] == '\0' && s[i] != '\0')
// 				return (-1);
// 		}
// 		if (s[i] == ' ')
// 			i++;
// 		else if (s[i] != ' ' && s[i] != '\0')
// 		{
// 			len ++;
// 			while (s[i] != ' ' && s[i] != '\0')
// 				i++;
// 		}
// 	}
// 	return (len);
// }

// int	countWords(char *str, t_command *com)
// {
// 	while (*str) 
// 	{
// 	if (*str == ' ' || *str == '\t' || *str == '\n')
// 		{
// 			if (!com->insidequotes) 
// 				com->inword = 0;
// 		} 
// 		else if (*str == '"') 
// 		{
// 			com->insidequotes = !com->insidequotes;
// 			if (!com->insidequotes && com->inword == 0)
// 			{
// 				com->inword = 1;
// 				com->count++;
// 			}
// 		}
// 		else if (com->inword == 0)
// 		{
// 			com->inword = 1;
// 			com->count++;
// 		}
// 		str++;
// 	}
// 	return (com->count);
// }


// char    **ft_sep(const char *s, t_base *base)
// {
//     int i;
//     int j;
//     int word;
//     char **strs;

//     i = 0;
//     j = 0;
//     word = ft_nbword(const char *s, base->command);
// 	word = malloc(sizeof(char **) * word);
// 	{
		
// 	}
// }

