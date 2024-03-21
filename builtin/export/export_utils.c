/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:51:40 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 16:51:41 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_more_link(t_env *chain, char *env, t_base *base)
{
	t_env	*link;

	if (!chain || !env)
		return ;
	link = get_link(chain, env);
	if (!link)
		return ;
	ft_putstr_fd(link->name, base->fd_out);
	ft_putstr_fd("\n", base->fd_out);
	link->name = ft_strndup(env, ft_is_that_char(env, '='));
	if (there_is_equal(env) == 1)
		link->value = ft_dup_value(env);
	else
		link->value = NULL;
}

void	add_more_link(t_env **chain, char *env)
{
	t_env	*link;
	t_env	*last_link;
	char	*equal_ptr;
	char	*value_start;
	char	*end_quote;

	link = malloc(sizeof(*link));
	if (!link) return ;
	{
		link->next = NULL;
		equal_ptr = strchr(env, '=');
	}
	if (equal_ptr != NULL)
	{
		link->name = ft_strndup(env, equal_ptr - env);
		value_start = equal_ptr + 1;
		if (*value_start == '"')
		{
			end_quote = ft_strchr(value_start + 1, '"');
			if (end_quote != NULL)
				link->value = ft_strndup(value_start,
						end_quote - value_start + 1);
			else
				link->value = ft_strdup(value_start);
		}
		else
			link->value = ft_strdup(value_start);
	}
	else
	{
		link->name = ft_strdup(env);
		link->value = NULL;
	}
	if (*chain == NULL)
	{
		*chain = link;
		link->previous = NULL;
	}
	else
	{
		last_link = *chain;
		while (last_link->next != NULL)
			last_link = last_link->next;
		last_link->next = link;
		link->previous = last_link;
	}
}

void	sorted(int argc, char **argv, t_base *base)
{
	int		i1;
	int		i2;
	char	*tmp;

	i2 = argc;
	i1 = 1;
	while (++i1 <= argc)
	{
		i2 = 1;
		while (++i2 <= argc - 1)
		{
			if (ft_strcmp(argv[i2], argv[i2 - 1]) < 0)
			{
				tmp = argv[i2];
				argv[i2] = argv[i2 - 1];
				argv[i2 - 1] = tmp;
			}
		}
	}
	i1 = 0;
	while (i1 < argc)
	{
		if (argv[i1][0] != '\0')
		{
			ft_putstr_fd("declare -x ", base->fd_out);
			ft_putstr_fd(argv[i1], base->fd_out);
			ft_putstr_fd("\n", base->fd_out);
		}
		i1++;
	}
}

t_env	*get_link(t_env *chain, char *env)
{
	t_env	*list;

	if (!chain)
		return (NULL);
	list = chain;
	while (list->next)
	{
		if (ft_strncmp(list->name, env, ft_is_that_char(env, '=') - 1) == 0)
			break ;
		list = list->next;
	}
	return (list);
}
