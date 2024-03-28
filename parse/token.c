/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:56:10 by vamologl          #+#    #+#             */
/*   Updated: 2024/03/15 13:56:11 by vamologl         ###   ########.fr       */
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

char	***ft_ultra_split(char *s)
{
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
	tab = ft_ultra_while(0, 0, tab, tmp);
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
	printf("s[i] = %c\n", s[i - 1]);
	if (s[i - 1] != '|')
	{
		ret = malloc(sizeof(char) * (i + 3));
		ret = ft_strdup(s);
		ret[i] = ' ';
		ret[i + 1] = '|';
		ret[i + 2] = '\0';
		// printf("ret = %s\n", ret);
		return (ret);
	}
	else
		return (s);
}

char	***build_tab(char *s)
{
	char	***tab;

	if (find_pipe(s) == -1)
		return (NULL);
	s = correct_input_for_parser(s);
	tab = ft_ultra_split(s);
	if (!tab)
		return (NULL);
	return (tab);
}

void	gest_dollar_multipipe(t_base *base)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	while (base->tableau && base->tableau[i] != NULL)
	{
		while (base->tableau[i][j])
		{
			if (base->tableau[i][j][0] != '\'')
			{
				if (is_there_char(base->tableau[i][j], '$') != 0)
				{
					if (ft_strncmp(base->tableau[i][j], "$?", 2) == 0)
					{
						tmp = ft_itoa(base->return_value);
						base->tableau[i][j] = ft_strdup(tmp);
						free(tmp);
					}
					else
						gest_dollar(base, j, i);
				}
			}
			else if (base->tableau[i][j][0] == '\'')
				base->tableau[i][j] = remove_simple_quote(base->tableau[i][j]);
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
	tab = ft_ultra_split(s);
	if (!tab)
		return (NULL);
	gest_dollar_multipipe(base);
	return (tab);
}
