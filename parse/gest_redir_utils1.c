/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_redir_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:22:07 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/14 16:22:08 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	correct_redirection_len(char *av)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * BUFFER_SZ);
	while (av[i])
	{
		if (av[i] == '>' || av[i] == '<')
		{
			ret[j++] = ' ';
			while (av[i] == '>' || av[i] == '<')
				ret[j++] = av[i++];
			ret[j++] = ' ';
		}
		else
			ret[j++] = av[i++];
	}
	free(ret);
	return (j);
}

char	*correct_redirection(char *av)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * BUFFER_SZ);
	while (av[i])
	{
		if (av[i] == '>' || av[i] == '<')
		{
			ret[j++] = ' ';
			while (av[i] == '>' || av[i] == '<')
				ret[j++] = av[i++];
			ret[j++] = ' ';
		}
		else
			ret[j++] = av[i++];
	}
	return (ret);
}

int	only_one_type_redir(char **tab)
{
	int	i;
	int	tmp_redir;

	i = 0;
	tmp_redir = -1;
	while (tab[i] && tmp_redir == -1)
	{
		if (ft_find_redirection(tab[i]) == 1)
			tmp_redir = 1;
		else if (ft_find_redirection(tab[i]) == 2)
			tmp_redir = 2;
		else if (ft_find_redirection(tab[i]) == 3)
			tmp_redir = 3;
		i++;
	}
	while (tab[i])
	{
		if (ft_find_redirection(tab[i]) != 0
			&& ft_find_redirection(tab[i]) != tmp_redir)
			return (0);
		i++;
	}
	return (1);
}