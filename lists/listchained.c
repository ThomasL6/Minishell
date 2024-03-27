/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listchained.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:53:46 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 15:53:47 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_shlvl_var(char *s2)
{
	int	i;

	i = ft_atoi(s2);
	i++;
	s2 = ft_itoa(i);
	i = 0;
	return (s2);
}

t_env	*find_last(t_env *head)
{
	if (NULL == head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	print_chain(t_env *chain, t_base *base)
{
	if (NULL == chain)
		return ;
	while (chain->next)
	{
		ft_putstr_fd(chain->name, base->fd_out);
		ft_putchar_fd('=', base->fd_out);
		chain = chain->next;
	}
}

char	*get_var_env(t_env *chain, char *name)
{
	char	*s;

	s = NULL;
	if (NULL == chain)
		return (NULL);
	while (chain->next)
	{
		if (ft_strcmp(name, chain->name) == 0)
		{
			s = ft_strdup(chain->value);
			return (s);
		}
		chain = chain->next;
	}
	return (NULL);
}

int	ft_put_string(t_env *chain, char *name, char *s)
{
	if (NULL == chain)
		return (0);
	while (chain->next)
	{
		if (ft_strcmp(name, chain->name) == 0)
		{
			chain->value = ft_strdup(s);
			if (ft_strcmp(s, chain->value) == 0)
				return (1);
			else
				return (0);
		}
		chain = chain->next;
	}
	return (0);
}
