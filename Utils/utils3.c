/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:51:28 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/23 15:51:32 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_if_storable(char *s)
{
	int i;
	int j;

	i = 0;
	if (!s[0])
		return (2);
	else if (s[0] == '=' && s[0])
		return (0);
	else if (s[0] >= '0' && s[0] <= '9' && s[0])
		return (0);
	else if (find_that_char(s, '=') == 1)
	{
		j = ft_is_that_char(s, '=');
		if ((int)ft_strlen(s) == j)
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

int is_char_or_num(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        return (1);
    else
        return (0);
}

int ft_strcmp_spe(char *string, char *compared, int srt, int end)
{
    int i = 0;
    while (string[srt] == compared[i] && string[srt] != '\0' &&
           compared[i] != '\0' && srt < end)
    {
        i++;
        srt++;
    }
    return (string[srt] - compared[i]);
}

void	ft_fdprint(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}