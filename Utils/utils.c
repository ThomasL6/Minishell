/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:19:10 by vamologl          #+#    #+#             */
/*   Updated: 2024/01/26 14:19:12 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int cmp_len(char *s1, char *s2)
{
    if(!s1 || !s2)
        return(0);
    if(ft_strlen(s1) == ft_strlen(s2))
        return(1);
    else
        return(0);
}

int	find_equal(char *s)
{
	int	i;

	if (!s)
	{
		printf("str in find equal is NULL");
		return (0);
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_dup_name(char *env)
{
	char 	*name;
	int		i = 0;

	name = malloc(sizeof(char *) * find_equal(env) + 1);
	if (!name)
		return (NULL);
	if (find_equal(env) != 0)
	{
		while (env[i] != '\0')
		{
			if (env[i] == '=')
				break;
			name[i] = env[i];
			i++;
		}
	}
	name[i] = '\0';
	return (name);
}

char	*ft_dup_value(char *env)
{
	char *value;
	int	i;
	int	j;

	value = malloc(sizeof(char *) * ft_strlen(env) - find_equal(env) + 1);
	if (!value)
		return (NULL);
	i = find_equal(env) + 1;
	j = 0;
	while (env[i] != '\0')
	{
		value[j] = env[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\t' || s[i] == ' ')
			i++;
		else 
			return (1);
	}
	return (0);
}


