/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:29 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/05 15:40:32 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	message_error(char *s, int flag)
{
	if (flag == 1)
		printf("Error - %s is a directory\n", s);
	if (flag == 2)
		printf("Error - %s No such file or directory\n", s);
	if (flag == 3)
		printf("Error - Command %s does not exist\n", s);
	free(s);
}

int	chk_directory2(char *str, int i)
{
	if (str[i] == '\0' || str[i] == ' ' \
		|| str[i] == '\t' || str[skip_whitespace(str, i)] == '\0')
	{
		printf("Error - filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		free(str);
		return (0);
	}
	else if (str[i] == '/')
	{
		i++;
		if ((str[i] == '\0' || str[i] == ' ' || str[i] == '.'\
		|| str[i] == '\t' || str[skip_whitespace(str, i)] == '\0'))
		{
			message_error(str, 1);
			return (0);
		}
	}
	return (1);
}

int	chk_directory3(char *str, int i)
{
	if (just_whitespace(str, i) == 1 || only_dots(str, i) == 1)
	{
		message_error(str, 1);
		return (0);
	}
	else if (only_dots(str, i) == -1)
	{
		message_error(str, 2);
		return (0);
	}
	return (1);
}

int	chk_directory4(char *str, int i)
{
	i++;
	if (many_dots(str, i) == 0)
	{
		message_error(str, 1);
		return (0);
	}
	else if (many_dots(str, i) == 1)
	{
		message_error(str, 2);
		return (0);
	}
	if (chk_directory2(str, i) == 0)
		return (0);
	return (1);
}

int	chk_directory(t_base *base)
{
	char	*str;
	int		i;

	i = 0;
	str = spaceless_strdup(base);
	if (str[i] == '.')
	{
		if (chk_directory4(str, i) == 0)
			return (0);
	}
	else if (str[i] == '/')
	{
		i++;
		if (chk_directory3(str, i) == 0)
			return (0);
	}
	free(str);
	return (1);
}
