/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:03:56 by vamologl          #+#    #+#             */
/*   Updated: 2023/04/17 13:46:33 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stddef.h>

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*l == '\0' || l == NULL)
		return ((char *)b);
	while (b[i] && i < len)
	{
		j = 0;
		if (b[i] == l[j])
		{
			while (i + j < len && b[i + j] == l[j])
			{
				j++;
				if (!l[j])
					return ((char *)&b[i]);
			}
		}
		i++;
	}
	return (NULL);
}
