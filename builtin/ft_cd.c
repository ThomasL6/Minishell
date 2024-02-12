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

void    own_cd(char *str)
{
    char    **s;

    s = ft_split(str, ' ');
    if(s[1] != NULL)
	{
		int x = chdir(s[1]);
		if(opendir(s[1]) == NULL)
		{
			if(x == -1)
				printf("cd: no such file or directory: %s\n", s[1]);
		}
	}
    ft_free_tab(s);
}