/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input_parser2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:36 by vamologl          #+#    #+#             */
/*   Updated: 2024/03/22 13:48:37 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	correct_redirection_len(char *av)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * BUFFER_SZ);
	while (av[i])
	{
		if (av[i] == '>' || av[i] == '<')
		{
			ret[j++] = ' ';
			while (av[i] == '>' || av[i] == '<')
				ret[j++] = av[i++];
			ret[j++] = ' ';
		}
		else
			ret[j++] = av[i++];
	}
	free(ret);
	return (j);
}

char	*init_input(char *s)
{
	char	*tmp;
	char 	*tmp2;

	tmp2 = correct_input_for_parser(s);
	free(s);
	tmp = correct_pipe_for_parser(tmp2);
	free(tmp2);
	return (tmp);
}
