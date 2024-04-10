/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <vamologl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:56:10 by vamologl          #+#    #+#             */
/*   Updated: 2024/04/10 11:08:44 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	***ft_ultra_while(int j, int k, char ***tab, char **tmp)
{
	int i;

	i = 0;
	while (tmp && i < ft_tablen(tmp))
	{
		tab[j] = (char **)malloc(sizeof(char *) * (tablen_pipe(tmp, i) + 1));
		if (!tab[j])
			return (NULL);
		k = 0;
		while (tmp[i] && ft_strcmp(tmp[i], "|") != 0)
		{
			tab[j][k] = ft_strdup(tmp[i]);
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

char	***ft_ultra_split(char *s, t_base *base)
{
	(void)base;
	char	**tmp;
	char	***tab;

	if (hm_pipe(s) == -1)
		return (NULL);
	tab = (char ***)malloc(sizeof(char ***) * (hm_pipe(s) + 2));
	if (!tab)
		return (NULL);
	tmp = ft_super_split(s);
	if (!tmp)
		return (NULL);
	tab = ft_ultra_while(0, 0, tab, &*tmp);
	base->tablen = (hm_pipe(s) + 2);
	free_tab(tmp);
	return (tab);
}

char	*check_last_pipe(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] != '|')
	{
		ret = malloc(sizeof(char) * (i + 3));
		ret = ft_strdup(s);
		ret[i] = ' ';
		ret[i + 1] = '|';
		ret[i + 2] = '\0';
		return (ret);
	}
	else
		return (s);
}

char	***build_tab(char *s, t_base *base)
{
	char	***tab;

	if (find_pipe(s) == -1)
		return (NULL);
	s = correct_input_for_parser(s);
	tab = ft_ultra_split(s, base);
	if (!tab)
		return (NULL);
	return (tab);
}

void	gest_dollar_multipipe(t_base *base)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (base->tableau && base->tableau[i] != NULL)
	{
		while (base->tableau[i][j] != NULL)
		{
			base->tableau[i][j] = modif_token(base->tableau[i][j], base);
			j++;
		}
		j = 0;
		i++;
	}
}

char ***pre_build_tab(t_base *base, char *s)
{
	char	***tab;

	if (find_pipe(s) == -1)
		return (NULL);
	tab = ft_ultra_split(s, base);
	if (!tab)
		return (NULL);
	(void)base;
	gest_dollar_multipipe(base);
	return (tab);
}
