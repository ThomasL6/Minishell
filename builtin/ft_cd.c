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

void	ft_free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// if chdir(fileName) failed
// -> perror(filename);

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
		ft_free_tab(s);
		base->return_value = 1;
		return ;
	}
	else if (s[1] != NULL)
	{
		x = chdir(s[1]);
		if (opendir(s[1]) == NULL)
		{
			if (x == -1)
			{
				base->return_value = 1;
				perror(s[1]);
				ft_free_tab(s);
				return ;
			}
		}
	}
	base->return_value = 0;
	ft_free_tab(s);
}
