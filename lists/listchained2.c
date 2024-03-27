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
	char	*var;
	char	*var2;
	char	*shlvl_value;

	var = ft_dup_name(env);
	if (!var || !(link = malloc(sizeof(*link))))
	{
		free(var);
		return ;
	}
	link->next = NULL;
	link->name = ft_strjoin(var, "=");
	free(var);
	if (!link->name)
	{
		free(link);
		return ;
	}
	var2 = ft_dup_value(env);
	if (!var2)
	{
		free(link->name);
		free(link);
		return ;
	}
	link->value = ft_strdup(var2);
	free(var2);
	if (ft_strcmp(link->name, "SHLVL=") == 0)
	{
		shlvl_value = ft_shlvl_var(link->value);
		if (shlvl_value)
		{
			free(link->value);
			link->value = shlvl_value;
		}
	}
	if (*chain == NULL)
		*chain = link;
	else
	{
		last_link = find_last(*chain);
		last_link->next = link;
		link->previous = last_link;
	}
}

void	initial_chain(t_env **chain, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		if (!chain)
			return ;
		add_link(chain, env[i]);
		i++;
	}
}
