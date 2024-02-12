/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:42:53 by vamologl          #+#    #+#             */
/*   Updated: 2023/04/17 15:13:41 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)str;
	while (i < n)
	{
		d[i++] = (unsigned char)c;
	}
	str = (void *)d;
	return (d);
}
