/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:17:40 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/26 15:17:42 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error(int i, t_base *base)
{
	if (i == 0)
	{
		ft_putstr_fd("Error -", 1);
		ft_putstr_fd(base->tableau[0][0], 1);
		ft_putstr_fd(" command not found\n", 1);
	}
	else if (i == 1)
	{
		ft_putstr_fd("exit not free'd\n", 1);
		exit_prog(0, base->env, base);
		exit(1273);
	}
}

int	nb_char(char *s)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = strlen(s);
	j--;
	while ((s[j] == ' ' || s[j] == '\t') && j > 0)
		j--;
	if (j < 0)
		return (-1);
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	count = 0;
	while (i <= j)
	{
		i++;
		count++;
	}
	return (count);
}