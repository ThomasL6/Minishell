/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:24:50 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/19 11:24:54 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "include/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h> // For debugging

int find_that_char(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int ft_strlen(const char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

int	ft_is_that_char(const char *s, int c) // return len before the char
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (ft_strlen(s));
}



int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int check_if_storable(char *s)
{
	int i;
	int j;

	i = 0;
	if (!s[0])
		return (0);
	else if (s[0] == '=' && s[0])
		return (0);
	else if (s[0] >= '0' && s[0] <= '9' && s[0])
		return (0);
	else if (find_that_char(s, '=') == 1)
	{
		j = ft_is_that_char(s, '=');
		if (ft_strlen(s) == j)
			return (2);
		while (i < j)
		{
			if (ft_isalnum(s[i]) == 0)
				return (0);
			else
				i++;
		}
	}
	return (1);
}

int main(int ac, char **av)
{
    int i = 1;

    while (i < ac)
    {
        printf("%d\n", check_if_storable(av[i]));
        i++;
    }
    return (0);
}

