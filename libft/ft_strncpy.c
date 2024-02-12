/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:42:28 by vamologl          #+#    #+#             */
/*   Updated: 2023/03/09 13:36:13 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/*#include<string.h>
#include<stdio.h>

int	main(void)
{
	char	dst[] = "00000000000000000000000000";
	char	src[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char	src1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	printf("%s\n", ft_strncpy(dst, src, 10));
	printf("%s\n", strncpy(dst, src1, 10));
}*/
