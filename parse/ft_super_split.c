/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <vamologl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:59:53 by thlefebv          #+#    #+#             */
/*   Updated: 2024/04/04 15:56:11 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static inline int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

static inline int	modif_edge(char c, char edge)
{
	if (edge == ' ')
		return (c);
	else if (c != edge)
		return (edge);
	else
		return (' ');
}

int	ft_super_countwords(const char *s)
{
	int		i;
	int		count;
	char	edge;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(s))
	{
		edge = ' ';
		while (s[i] == edge)
			i++;
		if (i >= (int)ft_strlen(s))
			break ;
		if (is_quote(s[i]))
			edge = modif_edge(s[i++], edge);
		count++;
		while (i < (int)ft_strlen(s) && s[i] != ' ')
		{
			if (is_quote(s[i]))
				edge = modif_edge(s[i], edge);
			i++;
		}
		i++;
	}
	return (count);
}

char	*ft_skip_spaces(char *s)
{
	while (*s && *s == ' ')
		s++;
	return (s);
}

int	ft_get_word_size(const char *s)
{
	int		size;
	char	quote;

	quote = 0;
	size = 0;
	while (s[size])
	{
		if (s[size] == '\"' && quote == 0)
			quote = '\"';
		else if (s[size] == '\'' && quote == 0)
			quote = '\'';
		else if (s[size] == ' ' && quote == 0)
			break ;
		else if (s[size] == quote)
			quote = 0;
		size++;
	}
	return (size);
}

char	*ft_extract_word(char const *s, int size)
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

char	**ft_super_split(char *s)
{
	char	**strs;
	int		j;
	int		word_count;
	int		word_size;

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
			while (j > -1)
				free(strs[j--]);
			free(strs);
			free(s);
			return (NULL);
		}
		j++;
		s += word_size;
	}
	strs[j] = NULL;
	if (!s)
		free(s);
	return (strs);
}
