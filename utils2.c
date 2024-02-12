/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:10:29 by vamologl          #+#    #+#             */
/*   Updated: 2024/01/26 14:10:30 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	*ft_find_quote(char *s)
{
	char *buff;
	int	flag = 0;
	int	i = 0;	// end
	int e = 0;	// start
	int	indx = 0;

	while (s[i] != '\0')
	{
		if (s[i] == 39 && flag == 0) // find first flag
		{
			e = i;
			flag = 1;
		}
		else if (s[i] == 39 && flag == 1) // find second flag
		{
			flag = 2;
			break ;
		}
		i++;
	}
	if (flag != 2)
		return (NULL);
	buff = malloc(i - e + 1);
	e++;
	while (e < i)
	{
		buff[indx] = s[e];
		indx++;
		e++;
	}
	buff[indx] = '\0';
	return (buff);
}

char	**ft_get_text(char *s)
{
	char **tab;
	int i;
	int j;
	int	indx;
	int jndx;

	indx = 0;
	tab = malloc(sizeof(char **) * ft_nbword(s, ' ') + 1);
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == '\t' || s[i] == ' ')
			i++;
		j = i;
		while (s[i] != '\t' && s[i] != ' ') 
			i++;
		jndx = 0;
		tab[indx] = malloc(sizeof(char *) * (i - j) + 1);
		while (j < i)
		{
			tab[indx][jndx] = s[j];
			j++;
			jndx++;
		}
		indx++;
	}
	return (tab);
}
