/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:48:42 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 16:48:44 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_link(t_env **chain, char *var_name)
{
	t_env	*link;

	link = *chain;
	while (link != NULL)
	{
		if (strncmp(link->name, var_name, ft_is_that_char(var_name, '=')) == 0)
		{
			if (link->previous != NULL)
				link->previous->next = link->next;
			else
				*chain = link->next;
			if (link->next != NULL)
				link->next->previous = link->previous;
			free(link->name);
			free(link->value);
			free(link);
			return ;
		}
		link = link->next;
	}
}

void	remove_old_env(t_base *base, char *var_name)
{
	int	i;
	int	shift;

	i = 0;
	shift = 0;
	while (base->env_old[i])
	{
		if (ft_strncmp(var_name, base->env_old[i],
				ft_is_that_char(var_name, '=')) == 0)
		{
			ft_bzero(base->env_old[i], ft_strlen(base->env_old[i]));
			shift = 1;
		}
		else if (shift)
		{
			base->env_old[i - 1] = base->env_old[i];
			base->env_old[i] = NULL;
		}
		i++;
	}
}

void	ft_unset(t_base *base)
{
	int	i;

	i = 1;
	ft_putstr_fd("ft_unset\n", base->fd_out);
	ft_putchar_fd('\n', base->fd_out);
	while (base->tableau[0][i])
	{
		remove_link(&base->env, base->tableau[0][i]);
		remove_old_env(base, base->tableau[0][i]);
		i++;
	}
}
