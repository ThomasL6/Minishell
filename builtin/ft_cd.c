/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <vamologl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:23:48 by thlefebv          #+#    #+#             */
/*   Updated: 2024/04/05 14:46:19 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	own_cd2(char **s, t_base *base, int x)
{
	char *to_free;
	
	if (s[1] && ft_strcmp(s[1], "~") == 0)
	{
		to_free = get_var_env(base->env, "HOME=");
		x = chdir(to_free);
		if (to_free)
			free(to_free);
	}
	else
	{	
		x = chdir(s[1]);
		if (opendir(s[1]) == NULL)
		{
			if (x == -1)
			{
				base->return_value = 1;
				perror(s[1]);
				free_tab(s);
				return ;
			}
		}
	}
	base->return_value = 0;
}

void	own_cd3(char **s, t_base *base)
{
	perror(s[1]);
	free_tab(s);
	base->return_value = 1;
	return ;
}

void	own_cd(char *str, t_base *base)
{
	int		x;
	char	**s;
	char	*to_free;

	s = ft_split(str, ' ');
	if (s[1] == NULL)
	{
		to_free = get_var_env(base->env, "HOME=");
		x = chdir(to_free);
		if (to_free)
			free(to_free);
	}
	if (ft_tablen(s) > 2)
	{
		own_cd3(s, base);
		return ;
	}
	else if (s[1] != NULL)
	{
		own_cd2(s, base, x);
		return ;
	}
	base->return_value = 0;
	free_tab(s);
}
