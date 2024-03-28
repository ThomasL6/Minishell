/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:49:03 by vamologl          #+#    #+#             */
/*   Updated: 2024/03/07 11:49:05 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab_get_exec(char **tab)
{
	int i;

	i = 0;
    if (tab)
    {
		while (tab[i] != NULL)
		{
            free(tab[i]);
			i++;
        }
        free(tab);
    }
}

char	**get_exec(char **tab)
{
    char	**ret;
    int		k;
    int		i;
    int		j;

    i = 0;
    k = 0;
    ret = NULL;
    if (!tab)
        return (NULL);
    while (tab[i] && ft_find_redirection(tab[i]) != 0)
        i += 2;
    j = i;
    while (tab[j] && ft_find_redirection(tab[j]) == 0)
        j++;
    ret = (char **)malloc(sizeof(char *) * (j - i + 1));
	if (!ret)
	{
		perror("fuck you get exec");
		return (NULL);
	}
    while (i < j)
    {
        ret[k] = ft_strdup(tab[i]);
        i++;
        k++;
    }
    ret[k] = NULL;
    free_tab_get_exec(tab);
    return (ret);
}

void	set_output(char **str, t_base *base)
{
	int	i;
	int	j;
	int	tmp;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (ft_find_redirection(str[i]) == 1)
		{
			tmp = open(str[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(tmp, base->fd_out);
			j++;
		}
		else if (ft_find_redirection(str[i]) == 2)
		{
			tmp = open(str[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(tmp, base->fd_out);
			j++;
		}
		i++;
	}
}

void	set_input(char **str, t_base *base)
{
	int	i;
	int	j;
	int	tmp;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (ft_find_redirection(str[i]) == 3)
		{
			tmp = open(str[i + 1], O_RDONLY, 0644);
			dup2(tmp, base->fd_in);
			j++;
		}
		i++;
	}
}

void	multi_redir2(char **str, t_base *base, int j)
{
	while (*str)
	{
		if (ft_find_redirection(*str) == 1
			|| ft_find_redirection(*str) == 2)
		{
			set_output(str, base);
			base->fd_in = 0;
			break ;
		}
		else if (ft_find_redirection(*str) == 3)
		{
			set_input(str, base);
			base->fd_out = 1;
			break ;
		}
		else if (ft_find_redirection(*str) == 4)
		{
			ft_double_lredir(base, j);
			base->fd_out = 1;
			base->fd_in = 0;
			break ;
		}
		str++;
	}
}

void	multi_redir(char **str, t_base *base, int j)
{
	if (only_one_type_redir(str))
		multi_redir2(str, base, j);
	else
	{
		ft_double_lredir(base, j);
		set_input(str, base);
		set_output(str, base);
	}
}
