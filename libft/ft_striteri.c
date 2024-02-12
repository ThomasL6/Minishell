/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:39:16 by vamologl          #+#    #+#             */
/*   Updated: 2023/04/21 15:07:44 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;
	int		i1;

	i = 0;
	i1 = 0;
	if (s != NULL && f != NULL)
	{
		i = ft_strlen(s);
		while (i1 < i)
		{
			(*f)(i1, s);
			s++;
			i1++;
		}
	}
}
