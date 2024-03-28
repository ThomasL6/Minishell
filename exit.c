/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:56:02 by vamologl          #+#    #+#             */
/*   Updated: 2024/01/23 11:56:06 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ms_exit_message(t_base *base)
{
	ft_putstr_fd("exit", base->fd_out);
	ft_putchar_fd('\n', base->fd_out);
	ft_putstr_fd("/-------------------", base->fd_out);
	ft_putchar_fd(92 , base->fd_out);
	ft_putchar_fd('\n', base->fd_out);
	ft_putstr_fd("| Goodbye Minishell |\n", base->fd_out);
	ft_putchar_fd(92 , base->fd_out);
	ft_putstr_fd("-------------------/\n", base->fd_out);
}

void	message(int i, t_base *base)
{
	if (i == 1)
	{
		base->fd_out = 1;
		ms_exit_message(base);
		// printf("\n\033[1;91mGoodbye Minishell\n\033");
	}
}

void	exit_prog(int i, void *ptr, t_base *base)
{
    if (1 == i) // ctrl - D
    {
        message(i, base);
        free(ptr);
    }
}

void    free_chain(t_env **chain, t_base *base)
{
	(void)base;
    t_env   *link;
    t_env   *ptr;

	if (!chain)
		return ;
	link = *chain;
	while (link)
	{
		ptr = link->next;
		free(link->value);
		free(link->name);
		free(link);
		link = ptr;
	}
	*chain = NULL;
}

void	free_long_tab(char ***tab)
{
	int i;
	int j;

	i = 0;
	if (!tab)
		return ;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
}

void	free_base(t_base *base)
{
	if (base->tableau)
		free(base->tableau);
	if (base->input)
		free(base->input);
	if (base->user)
		free(base->user);
	if (base->output_file)
		free(base->output_file);
	if (base->command)
		free(base->command);
	close(base->terminal_in);
	close(base->terminal_out);
	close(base->fd_out);
	close(base->fd_in);
	// close(base->ft_custom_exit);
	free_chain(&base->env, base);
}

void	ft_exit(t_base *base, int i)
{

	if (i == 2)
	{
		free_base(base);
		message(1, base);
		exit(0);
	}
	else if (base->tableau[i][0])
	{
		if (base->tableau[i][1] == NULL)
		{
			free_base(base);
			message(1, base);
			exit(0);
		}
	}
	ft_putstr_fd("exit: too many arguments\n", base->fd_out);
	return ;
}
