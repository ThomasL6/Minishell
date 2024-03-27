/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:46:13 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 16:46:15 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_list_env(t_env *env_struct, t_base *base)
{
	if (!env_struct)
		return ;
	while (env_struct)
	{
		if (env_struct->name[ft_strlen(env_struct->name) - 1] == '=')
		{
			if (env_struct->name && env_struct->value)
			{
				ft_putstr_fd(env_struct->name, base->fd_out);
				ft_putstr_fd(env_struct->value, base->fd_out);
				ft_putstr_fd("\n", base->fd_out);
			}
			else
				ft_putstr_fd("name and value not set\n", base->fd_out);
			env_struct = env_struct->next;
		}
		else
			env_struct = env_struct->next;
	}
}

void	ft_print_env(t_base *base, char *name, int srt, int end)
{
	if (!base->env)
		return ;
	while (base->env)
	{
		if (ft_strcmp_spe(name, base->env->name, srt, end) == 0)
		{
			ft_putstr_fd(base->env->value, base->fd_out);
			return ;
		}
		base->env = base->env->next;
	}
}

void	own_env(t_base *base, int i)
{
	if (base->tableau && base->tableau[i][0])
	{
		if (base->tableau[i][1])
		{
			ft_putstr_fd("env: ", base->fd_out);
			ft_putstr_fd(base->tableau[i][1], base->fd_out);
			ft_putstr_fd(": No such file or directory\n", base->fd_out);
			base->return_value = 127;
			return ;
		}
		else
		{
			print_list_env(base->env, base);
			base->return_value = 0;
		}
		return ;
	}
	perror("ERROR: env");
}
