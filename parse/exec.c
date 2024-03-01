/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:25:18 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/19 11:25:28 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int fd_write(int fd, char *str, int flag)
{
    write(fd, str, strlen(str));
    if (flag == 1)
        write(fd, "\n", 1);
    write(STDOUT_FILENO, str, strlen(str));
    if (flag == 1)
        write(STDOUT_FILENO, "\n", 1);
    return strlen(str);
}

//penser a faire un return error
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_my_env(char *name, char **env)
{
	int		i;
	char	*ret;
	char	**str_env;

	i = 0;
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

int	ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static char    *build_exec_path(char *path, char *cmd)
{
    char    *exec_path;
    char    *tmp;

    exec_path = ft_strjoin(path, "/");
    tmp = exec_path;
    exec_path = ft_strjoin(exec_path, cmd);
    free(tmp);
    return (exec_path);
}

char    *get_path_tab(char *input, char **env)
{
    char    **path;
    char    **s_cmd;
    char    *exec_path;
    int        i;

    if (access(input, F_OK | X_OK) == 0)
        return (ft_strdup(input));
    path = ft_split(get_my_env("PATH=", env), ':');
    s_cmd = ft_split(input, ' ');
    i = 0;
    while (path && path[i])
    {
        exec_path = build_exec_path(path[i], s_cmd[0]);
        if (access(exec_path, F_OK | X_OK) == 0)
        {
            free_tab(s_cmd);
            free_tab(path);
            return (exec_path);
        }
        free(exec_path);
        i++;
    }
    free_tab(s_cmd);
    free_tab(path);
    return (NULL);
}

int	is_there_redir(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (ft_find_redirection(s[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int ft_spe_execve(char *fp, char **av, char **tab, t_base *base)
{
	pid_t	pid;
	int fd_tmp;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		fd_tmp = dup(1); // fd_tmp = store the current stdout
		dup2(base->fd_out, 1); //change the current stdout to the file descriptor
		dprintf(base->ft_custom_exit, "%d\n", base->fd_out); // to remove
		if (!execve(fp, av, tab))
		{
			free_tab(av);
			close(base->fd_out); // if failed to execute, close the file descriptor
			dprintf(base->ft_custom_exit, "ft_exec : execve failed\n");
		}
		dup2(fd_tmp, 1); // restore the current stdout
	}
	waitpid(pid, NULL, 0);
	return (0);
}

// faire une fonction get redir qui ouvre fd au type de redir (a la place de while 1)
// fermer les fd apres
// le faire foncitonner avec les autre fonction

void ft_basic_redir(char *fp, char **av, char **tab, t_base *base)
{
	int i;
	int fd_tmp;
	char **tmp;
	(void)av;

	fd_tmp = base->fd_out;
	i = 0;
	tmp = malloc(sizeof(char **) * (ft_tablen(base->tableau[0])));
	while (ft_strncmp(base->tableau[0][i], ">", ft_strlen(base->tableau[0][i])) != 0 && base->tableau[0][i])
	{
		if (base->tableau[0][i + 1] == NULL)
		{
			base->fd_out = 1;
			return ;
		}
		tmp[i] = base->tableau[0][i];
		i++;
	}
	tmp[i] = NULL;
	if (base->tableau[0][i + 1] == NULL)
	{
		base->fd_out = 1;
		free(tmp);
		return ;
	}
	i++;
	// base->fd_out = open(base->tableau[0][i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	base->fd_out = open(base->tableau[0][i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_spe_execve(fp, tmp, tab, base);
	base->fd_out = fd_tmp;
}


int	ft_exec(char *fp, char **av, char **tab, t_base *base)
{
	// int		tmp1;
	(void)base;

	int i = 0; // to remove

	ft_putstr_fd("in ft_exec\n", base->ft_custom_exit);
	if (is_there_redir(av))
		ft_basic_redir(fp, av, tab, base);
	else
	{
		dprintf(base->ft_custom_exit, "about to execute |"); // to remove
		while (av[i])	 // to remove
			dprintf(base->ft_custom_exit, "%s ", av[i++]); // to remove
		dprintf(base->ft_custom_exit, "|\n"); // to remove
		ft_spe_execve(fp, av, tab, base);
		ft_putstr_fd("execute done\n", base->ft_custom_exit); // to remove
	}
	return (0);
}
	/*
	dup2(fd_out, 1);
	dup2(fd_in, 0);
	if (-1 == excve())
     error
	*/

int ft_exec_prog(char **av, t_base *base)
{
	char *fp;

	fp = get_path_tab(av[0], base->env_old);
	if(!fp)
		return(0);
	if (fp == NULL)
	{
		printf("Failed to find executable\n");
		return (0);
	}
	ft_exec(fp, av, base->env_old, base);
	//perror("execve failed");
	return (1);
}
