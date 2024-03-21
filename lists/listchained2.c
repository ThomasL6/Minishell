/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listchained2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:57:44 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 15:57:45 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_link(t_env **chain, char *env)
{
	t_env	*link;
	t_env	*last_link;

	link = malloc(sizeof * link);
	if (NULL == link)
		return ;
	link->next = NULL;
	link->name = NULL;
	link->value = NULL;
	link->name = ft_strjoin(ft_dup_name(env), "=");
	link->value = ft_dup_value(env);
	if (ft_strcmp(link->name, "SHLVL=") == 0)
		link->value = ft_shlvl_var(link->value);
	if (*chain == NULL)
	{
		*chain = link;
		link->previous = NULL;
	}
	else
	{
		last_link = find_last(*chain);
		last_link->next = link;
		link->previous = last_link;
	}
}

void	initial_chain(t_env **chain, char **env, t_base *base)
{
	int	i;

	i = 0;
	if (!env)
	{
		ft_putstr_fd("Env t exist\n", base->fd_out);
		return ;
	}
	while (env[i])
	{
		if (!chain)
			return ;
		add_link(chain, env[i]);
		i++;
	}
}
