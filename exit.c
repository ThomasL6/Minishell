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


void	message(int i)
{
	if (i == 1)
		printf("\n\033[1;91mGoodbye Minishell\n\033");
}

void	exit_prog(int i, void *ptr)
{
    if (1 == i) // ctrl - D
    {
        message(i);
        free(ptr);
    }
	
}

void    free_chain(t_env **chain)
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
	printf("\n- Chained free'd\n");
}

void	ft_exit(t_env **chain)
{
	free_chain(chain);
	message(1);
	exit(0);
}