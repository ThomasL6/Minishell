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

// void	ft_exit(t_base *base)
// {
// 	if (base->input != NULL)
// 		free(base->input);
// 	if (base->user != NULL)
// 		free(base->user);
// 	if (base->cur_pwd != NULL)
// 		free(base->cur_pwd);
// 	if (base->env != NULL)
// 		free_chain(base->env);
// 	if (base->env_old != NULL)
// 		free(base->env_old);
// 	if (base->output_file != NULL)
// 		free(base->output_file);
// 	if (base->env_path != NULL)
// 		free(base->env_path);
// 	if (base->command != NULL)
// 		free(base->command);
// 	if (base->tableau != NULL)
// 		free(base->tableau);
// 	close(base->ft_custom_exit);
// 	exit(g_signal);

// }

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
		free(link);
		link = ptr;
	}
	*chain = NULL;
}

void	ft_exit(t_base *base)
{
	ft_putstr_fd("-- closed Minishell --\n", base->ft_custom_exit);
	free_chain(&base->env, base);
	message(1, base);
	free(base->user);
	exit(0);
}