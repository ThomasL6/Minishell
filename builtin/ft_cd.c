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

void ft_free_tab(char **str)
{
    int i = 0;
    while (str[i] != NULL)
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void    own_cd(char *str, t_base *base)
{
    char    **s;
    int     x;

    s = ft_split(str, ' ');
    if (s[1] == NULL)
        x = chdir(get_var_env(base->env, "HOME="));
    else if(s[1] != NULL)
	{
		x = chdir(s[1]);
		if(opendir(s[1]) == NULL)
		{
			if(x == -1)
            {
                ft_putstr_fd("cd: no such file or directory: ", base->fd_out);
                ft_putstr_fd(s[1], base->fd_out);
                ft_putstr_fd("\n", base->fd_out);
            }
		}
	}
    ft_free_tab(s);
}
