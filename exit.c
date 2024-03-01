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
    t_env   *link;
    t_env   *ptr;

	if (!chain)
		return ;
	link = *chain;
	while (link)
	{
		ptr = link->next;
		free(link);
		link = ptr;
	}
	*chain = NULL;
	ft_putstr_fd("\n- Chained free'd\n", base->fd_out);
	// printf("\n- Chained free'd\n");
}

void	ft_exit(t_base *base)
{
	ft_putstr_fd("-- closed Minishell --\n", base->ft_custom_exit);
	free_chain(&base->env, base);
	message(1, base);
	free(base->user);
	exit(0);
}