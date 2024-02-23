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

// int ft_write_redir(char **av, int fd, int flag)
// {
// 	if (atoi(av[1]) && fd && read(fd, NULL, 1) <= 1)
// 		flag = 1; // if file is empty
// 	if (fd == -1)
// 	{
// 		printf("Error - file not found\n");
// 		return (-1);
// 	}
// 	else if (av[3])
// 	{
// 		fd_write(fd, av[3], flag);
// 		close(fd);
// 	}
// 	else
// 	{
// 		printf("Error - no text to write\n");
// 		return (-2);
// 	}
// 	return (0);
// }

int ft_redir(t_base *base)
{
    char *str;
    int fd;
    int i;
    int symb;

    i = 0;
    str = base->input;
    symb = ft_find_redirection(&str[i], i);
    while (str[i])
    {
        if (symb == 1)
        {
            fd = open(&str[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("Error opening file");
                return (-1);
            }
            // Rediriger stdout vers le fichier
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("Error redirecting stdout");
                close(fd);
                return (-1);
            }
            close(fd); // Fermer le descripteur de fichier du fichier ouvert
            break; // Arrêter la recherche de redirections après avoir trouvé une redirection >
        }
        else if (symb == 2)
        {
            fd = open(&str[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("Error opening file");
                return (-1);
            }
            // Rediriger stdout vers le fichier
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("Error redirecting stdout");
                close(fd);
                return (-1);
            }
            close(fd); // Fermer le descripteur de fichier du fichier ouvert
            break; // Arrêter la recherche de redirections après avoir trouvé une redirection >>
        }
        i++;
    }
    return (0);
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



int	ft_exec(char *fp, char **av, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
        if (env)
		    execve(fp, av, env);
	waitpid(pid, NULL, 0);
	return (0);
}


int ft_exec_prog(char **av, t_base *base)
{
	char *fp;

	fp = get_path_tab(av[0], base->env_old);
	if(!fp)
		return(0);
	if (ft_redir(base) == -1)
	{
		printf("Redirection failed\n");
		return (0);
	}
	if (fp == NULL)
	{
		printf("Failed to find executable\n");
		return (0);
	}
	ft_exec(fp, av, base->env_old);
	//perror("execve failed");
	return (1);
}
