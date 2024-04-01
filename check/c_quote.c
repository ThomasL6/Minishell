/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:40 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/05 13:08:42 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	chk_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != 0)
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
			{
				if (s[i++] == 0)
					return (0);
			}
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				if (s[i++] == 0)
					return (0);
			}
		}
	}
	return (1);
}
