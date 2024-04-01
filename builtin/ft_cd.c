/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:23:48 by thlefebv          #+#    #+#             */
/*   Updated: 2024/02/06 13:23:49 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	own_cd2(char **s, t_base *base, int x)
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

void	own_cd(char *str, t_base *base)
{
	char	**s;
	int		x;

	s = ft_split(str, ' ');
	if (s[1] == NULL)
		x = chdir(get_var_env(base->env, "HOME="));
	if (s[2] != NULL)
	{
		perror(s[1]);
		free_tab(s);
		base->return_value = 1;
		return ;
	}
	else if (s[1] != NULL)
		own_cd2(s, base, x);
	base->return_value = 0;
	free_tab(s);
}
