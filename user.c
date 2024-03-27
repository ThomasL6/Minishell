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

void    init_user2(char *s, char *tmp, int k, t_base *base)
{
    int        i;
    int        j;
    char    *tmp2;
    char    *usertmp;

    i = 6;
    j = 0;
    while (i < k)
    {
        tmp[j] = s[i];
        i++;
        j++;
    }
    tmp[j] = '\0';
    tmp2 = get_var_env(base->env, "USER=");
    base->user = ft_strjoin(tmp2, "@"); // malloc 1
    usertmp = base->user; // usertmp = malloc 1
    base->user = ft_strjoin(base->user, tmp); // malloc 2
    free(usertmp); // free(malloc 1);
    usertmp = base->user; // usertmp = malloc 2
    base->user = ft_strjoin(usertmp, ":~$ "); // malloc 3
    free(usertmp); // free(malloc 2)
    free(tmp2);
    free(tmp);
    free(s);
}

void	init_user(t_base *base)
{
	char	*s;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 6;
	j = 0;
	k = 6;
	tmp = NULL;
	s = NULL;
	s = get_var_env(base->env, "SESSION_MANAGER=");
	while (s[i] != '.' && s[i])
	{
		i++;
		j++;
		k++;
	}
	tmp = malloc(sizeof(char *) * j + 1);
	init_user2(s, tmp, k, base);
}
