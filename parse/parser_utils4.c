/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:33:12 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/26 11:33:14 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	no_command(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_find_redirection(av[i]) != 0)
			i += 2;
		else
			return (0);
	}
	return (1);
}

char	*remove_simple_quote(char *s)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = 1;
	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * ft_strlen(s) - 1);
	if (!ret)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\'')
	{
		ret[j] = s[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_sstrndup(char *s, int n, int start)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (0);
	while (s[start] && i < n)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strlen_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
	{
		if (s[i + 1] != '\0')
			return (i + 1);
		i++;
	}
	i++;
	while (s[i] && s[i] != '\"')
		i++;
	return (i);
}

void	ft_print_triple_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			printf("%s\n", tab[i][j]);
			j++;
		}
		i++;
	}
}