/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:39:18 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/05 13:39:19 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	chk_pipe_start(char *s) // return 1 if the first char is a pipe
{
	int i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == 124)
		return (1);
	return (0);
}

int	chk_pipe_end(char *s)
{
	int i;

	i = ft_strlen(s);
	i--;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	if (s[i] == '|')
		return (1);
	return (0);
}

// void	pipe_nb_com(t_base *base)
// {
// 	t_token *p_lst;

// 	p_lst = base->lst->head;
// 	base->nb_pipe = 0;
// 	base->nb_cmd = 0;
// 	base->nb_ind = 0;

// 	while (NULL != p_lst)
// 	{
// 		if (p_lst->type == 1)
// 			base->nb_pipe++;
// 		else
// 			base->nb_com++;
// 		p_lst = p_lst->next;
// 	}
// }

// void	only_one_command(t_base *base)
// {
// 	t_token	*lst_p;

// 	lst_p = base->lst->head;

// }
