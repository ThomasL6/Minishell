/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:52:50 by thlefebv          #+#    #+#             */
/*   Updated: 2024/02/06 10:52:52 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_pwd(t_base *base)
{
	char tmp[PATH_MAX];

	if(getcwd(tmp, PATH_MAX))
	{
		base->cur_pwd = tmp;
		printf("%s\n", base->cur_pwd);
		return (1);
	}
	return (0);
}
