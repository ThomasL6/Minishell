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

void ft_print_env(t_base *base, char *name, int srt, int end)
{
    if (NULL == &base->env)
        return;
    while (&base->env)
    {
        if (ft_strcmp_spe(name, base->env->name, srt, end) == 0)
        {
			ft_putstr_fd(base->env->value, base->fd_out);
            // printf("%s", &base->env->value);
            return;
        }
        base->env = base->env->next;
    }
}

int is_env(char *s, t_base *base, int i)
{
    int srt = i;
    int end;
    while (s[i])
    {
        i++;
        if ((s[i + 1] == ' ' || s[i + 1] == '\'' || s[i + 1] == '\"'))
            break;
		else if (!is_char_or_num(s[i + 1]))
			break ;
    }
    end = i;
    ft_print_env(base, s, srt, end);
    return (i - srt + 1); // Retourne le nombre de caractères traités 
}

void echo_verif_dollar(t_base *base, int i)
{
    int j;

	j = 0;
    while (base->tableau[0][i][j])
    {
        if (base->tableau[0][i][j] == '$' && base->tableau[0][i][0] != '\'')
        {
            j++;
            j += is_env(base->tableau[0][i], base, j);
        }
        else
        {
            if (base->tableau[0][i][j] != '\'' && base->tableau[0][i][j] != '\"')
				ft_putchar_fd(base->tableau[0][i][j], base->fd_out);
                // printf("%c", base->tableau[0][i][j]);
            j++;
        }
    }
    if (base->tableau[0][i + 1])
		ft_putchar_fd(' ', base->fd_out);
        // printf(" ");
}

void	write_echo(t_base *base, int i, int flag, int mode)
{
	if (mode == 0)
	{
		if (base->tableau[0][0] && !base->tableau[0][1])
		{
			ft_putchar_fd('\n', base->fd_out);
			// printf("\n");
			return;
		}
	}
	else if (mode == 1)
	{
		while (base->tableau[0][i])
		{
			echo_verif_dollar(base, i);
			i++;
		}
		if (flag == 0)
			ft_putchar_fd('\n', base->fd_out);
			// printf("\n");
	}
}

void own_echo(t_base *base)
{
	int flag;
	int i;
	int j;

	flag = 0;
	i = 1;
	j = 0;
	if (base->tableau[0][0] && !base->tableau[0][1])
		write_echo(base, i, flag, 0);
	else
	{
		if (base->tableau[0][i][j] == '-')
		{
			j++;
			while (base->tableau[0][i][j] == 'n')
				j++;
			if (base->tableau[0][i][j] == '\0')
			{
				flag = 1;
				i++;
			} 
		}
	}
	write_echo(base, i, flag, 1);
}
