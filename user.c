/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:24:07 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/06 13:24:11 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	init_user2(char *s, char *tmp, int k, t_base *base)
{
	int i;
	int j;

	i = 6;
	j = 0;
	while (i < k)
	{
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(s);
	base->user = ft_strjoin(ft_get_string(base->env, "USER"), "@");
	base->user = ft_strjoin(base->user, tmp);
	base->user = ft_strjoin(base->user, ":~$ ");
}

void	init_user(t_base *base)
{
	char *s;
	char *tmp;
	int i;
	int j;
	int k;

	i = 6;
	j = 0;
	k = 6;
	s  = ft_get_string(base->env, "SESSION_MANAGER");
	while (s[i] != '.' && s[i])
	{
		i++;
		j++;
		k++;
	}
	tmp = malloc(sizeof(char *) * j + 1);
	init_user2(s, tmp, k, base);
}

// void	init_base_struct(t_base *base)
// {
	// 
// }
