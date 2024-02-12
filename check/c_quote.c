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

int	chk_quote(char *s) // return 1 if every quotes are closed and 0 if not and no mix
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == 39) // 39 = ' (single quote)
		{
			i++;
			while (s[i] != 39)
			{
				if (s[i++] == 0)
					return (0); // not closed with ''
			}
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
			{
				if (s[i++] == 0)
					return (0); // not closed but with ""
			}
		}
		i++;
	}
	return (1);
}
