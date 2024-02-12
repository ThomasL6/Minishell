/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:37:53 by thlefebv          #+#    #+#             */
/*   Updated: 2024/02/01 10:37:55 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_list *lst, char *prompt, int type, t_base *base)
{
	t_token *new_link;
	t_token *last_link;

	new_link = malloc(sizeof(t_token));
	if (!new_link)
		return ;
	new_link->prompt = ft_gcstrdup(prompt, base);
	if (!new_link->prompt)
		return ;
	new_link->type = type;
	new_link->next = NULL;
	last_link = lst->head;
	if (!last_link)
	{
		lst->head = new_link;
		base->lst = lst;
	}
	else
	{
		while (last_link->next)
			last_link = last_link->next;
		last_link->next = new_link;
	}
	base->cmd++;
}

void	free_list(t_list *lst)
{
	t_token *current;
	t_token *tmp;

	current = lst->head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	lst->head = NULL;
}

void	show_link_list(t_list *lst)
{
	t_token *current;
	t_token *tmp;

	current = lst->head;
	while (current)
	{
		tmp = current;
		current = current->next;
		printf("token = %s, type = %d\n", tmp->prompt, tmp->type);
	}
}