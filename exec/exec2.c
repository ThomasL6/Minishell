/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:47:53 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/13 15:47:56 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	*get_my_env(char *name, char **env)
{
	int		i;
	char	*ret;
	char	**str_env;

	i = 0;
	ret = NULL;
	str_env = NULL;
	while (env[i])
	{
		str_env = ft_split(env[i], '=');
		if (str_env && ft_strncmp(name, str_env[0], ft_strlen(str_env[0])) == 0)
		{
			if (str_env[1] == NULL)
				continue ;
			ret = ft_strdup(str_env[1]);
			free_tab(str_env);
			return (ret);
		}
		i++;
		free_tab(str_env);
	}
	return (NULL);
}

// char	*build_exec_path(char *path, char *cmd)
// {
// 	char	*exec_path;
// 	char	*tmp;

// 	exec_path = ft_strjoin(path, "/");
// 	tmp = ft_strjoin(exec_path, cmd);
// 	free(exec_path);
// 	return (tmp);
// }

char	*build_exec_path(char *path, char *cmd)
{
	char *ret;
	char *tmp;
	char *tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp, cmd);
	free(tmp);
	ret = ft_strdup(tmp2);
	free(tmp2);
	return (ret);
}

char	*get_path_tab(char *input, char **env)
{
	char 	*tmp;
	char	**path;
	char	**s_cmd;
	char	*exec_path;
	int		i;

	path = NULL;
	if (access(input, F_OK | X_OK) == 0)
		return (ft_strdup(input));
	tmp = get_my_env("PATH=", env);
	path = ft_split(tmp, ':');
	free(tmp);
	s_cmd = ft_split(input, ' ');
	i = -1;
	while (path && path[++i])
	{
		exec_path = build_exec_path(path[i], s_cmd[0]);
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			free_tab(s_cmd); // Free s_cmd before returning
			free_tab(path);
			return (exec_path);
		}
		free(exec_path);
	}
	free_tab(s_cmd);
	free_tab(path);
	free(exec_path);
	return (NULL);
}

