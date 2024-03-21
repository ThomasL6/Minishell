/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:24:00 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 17:24:02 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote(const char *s, int i, char c)
{
	int	len;

	len = 0;
	i++;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len + 1);
}

int	ft_find_redirection(char *s)
{
	if (s)
	{
		if (ft_strcmp(s, ">") == 0)
			return (1);
		else if (ft_strcmp(s, ">>") == 0)
			return (2);
		else if (ft_strcmp(s, "<") == 0)
			return (3);
		else if (ft_strcmp(s, "<<") == 0)
			return (4);
		else if (ft_strncmp(s, "<<<", 3) == 0)
			return (-1);
		else if (ft_strncmp(s, ">>>", 3) == 0)
			return (-1);
	}
	return (0);
}

int	where_is_equal(const char *s, int i) // return len before the char
{
	int	start;

	start = i;
	while (s[i] != '=' && s[i] != '\0')
	{
		if (s[i] == '=')
			return (i - start);
		i++;
	}
	return (ft_strlen(s));
}

int	ft_strlen_wo_quote(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
int	skip_whitespace(char *string, int i)
{
	int	j;

	j = 0;
	while ((string[i + j] == ' ' || string[i + j] == '\b'
			|| string[i + j] == '\t'
			|| string[i + j] == '\n') && string[i + j] != 0)
		j++;
	return (j);
}