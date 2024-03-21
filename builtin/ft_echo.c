/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:09:18 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/02 14:09:19 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_env(char *s, t_base *base, int i)
{
	int	srt;
	int	end;

	srt = i;
	while (s[i])
	{
		i++;
		if ((s[i + 1] == ' ' || s[i + 1] == '\'' || s[i + 1] == '\"'))
			break ;
		else if (!is_char_or_num(s[i + 1]))
			break ;
	}
	end = i;
	ft_print_env(base, s, srt, end);
	return (i - srt + 1);
}

void    write_echo(t_base *base, int k)
{
    if (base->tableau[k][0] && !base->tableau[k][1])
    {
        ft_putchar_fd('\n', base->fd_out);
        return ;
    }

}

void    write_echo_alt(t_base *base, int i, int flag, int k)
{
    while (base->tableau[k][i])
    {
		ft_putstr_fd(base->tableau[k][i], base->fd_out);
		if (base->tableau[k][i + 1])
			ft_putchar_fd(' ', base->fd_out);
        i++;
    }
    if (flag == 0)
        ft_putchar_fd('\n', base->fd_out);
}


void	own_echo(t_base *base, int k)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 1;
	j = 0;
	if (base->tableau[k][0] && !base->tableau[k][1])
	{
		write_echo(base, k);
		base->return_value = 1;
	}
	else
	{
		if (base->tableau[k][i][j] == '-')
		{
			j++;
			while (base->tableau[k][i][j] == 'n')
				j++;
			if (base->tableau[k][i][j] == '\0')
			{
				flag = 1;
				i++;
			}
		}
	}
	write_echo_alt(base, i, flag, k);
	base->return_value = 0;
}
