/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:57:59 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/26 11:58:00 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	only_one_redir(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_find_redirection(s[i]) != 0)
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

void	ft_double_redir(char **av, t_base *base, int j)
{
	char	**tmp;
	int		i;

	(void)av;
	i = -1;
	tmp = malloc(sizeof(char **) * (ft_tablen(base->tableau[j])));
	while (base->tableau[j][++i] && ft_strncmp(base->tableau[j][i]
			, ">>", ft_strlen(base->tableau[j][i])) != 0)
	{
		if (!base->tableau[j][i + 1])
		{
			base->fd_out = 1;
			return ;
		}
		tmp[i] = base->tableau[j][i];
	}
	tmp[i] = NULL;
	if (!base->tableau[j][i + 1])
	{
		base->fd_out = 1;
		free(tmp);
		return ;
	}
	base->fd_out = open(base->tableau[j][++i],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	base->flag_redir = 0;
}

void	ft_basic_redir(char **av, t_base *base, int j)
{
	char	**tmp;
	int		i;

	(void)av;
	i = 0;
	tmp = malloc(sizeof(char **) * (ft_tablen(base->tableau[j])));
	while (ft_strncmp(base->tableau[j][i], ">"
		, ft_strlen(base->tableau[j][i])) != 0 && base->tableau[j][i])
	{
		if (base->tableau[j][i + 1] == NULL)
		{
			base->fd_out = 1;
			return ;
		}
		tmp[i] = base->tableau[j][i];
		i++;
	}
	tmp[i] = NULL;
	if (base->tableau[j][i + 1] == NULL)
	{
		base->fd_out = 1;
		free(tmp);
		return ;
	}
	free(tmp);
	i++;
	base->fd_out = open(base->tableau[j][i],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	base->flag_redir = 0;
}

int	ft_left_redir(char **av, t_base *base, int j)
{
	char	**tmp;
	int		i;

	(void)av;
	i = 0;
	tmp = malloc(sizeof(char **) * (ft_tablen(base->tableau[j])));
	while (ft_strncmp(base->tableau[j][i], "<",
		ft_strlen(base->tableau[j][i])) != 0 && base->tableau[j][i])
	{
		if (base->tableau[j][i + 1] == NULL)
		{
			base->fd_in = 0;
			return (1);
		}
		tmp[i] = base->tableau[j][i];
		i++;
	}
	tmp[i] = NULL;
	if (base->tableau[j][i + 1] == NULL)
	{
		base->fd_in = 0;
		free(tmp);
		return (1);
	}
	i++;
	base->fd_in = open(base->tableau[j][i], O_RDONLY, 0644);
	if (base->fd_in == -1)
	{
		perror(base->tableau[j][i]);
		return (-1);
	}
	base->flag_redir = 1;
	return (0);
}

void	ft_double_lredir(t_base *base, int j)
{
	int	i;

	i = 0;
	while (base->tableau[j][i] != NULL)
	{
		if (ft_strcmp(base->tableau[j][i], "<<") == 0)
		{
			// dprintf(base->ft_custom_exit, "found <<\n");
			here_doc(base->tableau[j][i + 1], base);
		}
		i++;
	}
	dup2(base->fd_out, 1);
	dup2(base->fd_in, 0);
}
