/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:59:53 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 16:59:55 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_super_countwords(const char *s)
{
	int	count;
	int	inside_word;

	count = 0;
	inside_word = 0;
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
	return (count);
}

const char	*ft_skip_spaces(const char *s)
{
	while (*s && *s == ' ')
		s++;
	return (s);
}

int	ft_get_word_size(const char *s)
{
	int	size;
	int	insidequotes;

	insidequotes = 0;
	size = 0;
	while (s[size])
	{
		if (s[size] == '\"')
			insidequotes = !insidequotes;
		else if (s[size] == ' ' && !insidequotes)
			break ;
		size++;
	}
	return (size);
}

char	*ft_extract_word(const char *s, int size)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < size)
	{
		word[i] = s[i];
		i++;
	}
	word[size] = '\0';
	return (word);
}

char	**ft_super_split(char const *s)
{
	char	**strs;
	int		j;
	int		word_count;
	int		word_size;
	int		k;

	k = 0;
	j = 0;
	word_count = ft_super_countwords(s);
	strs = malloc((word_count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (*s && j < word_count)
	{
		s = ft_skip_spaces(s);
		word_size = ft_get_word_size(s);
		if (j > 0 && *(s - 1) == '=' && word_size == 0)
			word_size++;
		strs[j] = ft_extract_word(s, word_size);
		if (!strs[j])
		{
			while (k++ < j)
				free(strs[k]);
			free(strs);
			return (NULL);
		}
		j++;
		s += word_size;
	}
	strs[j] = NULL;
	return (strs);
}
