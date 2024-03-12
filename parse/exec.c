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
		else if (ft_find_redirection(s[i]) == 2)
			return (2);
		else if (ft_find_redirection(s[i]) == 3)
			return (3);
		else if (ft_find_redirection(s[i]) == 4)
			return (4);
		i++;
	}
	return (0);
}

int ft_spe_execve(char **av, char **tab, t_base *base)
{
	pid_t	pid;
	int fd_tmp; //out
	int	fd_tmp2; //in

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		fd_tmp = dup(1); // fd_tmp = store the current stdout
		fd_tmp2 = dup(0); // fd_tmp2 = store the current stdin
		if(dup2(base->fd_out, 1) == -1) //change the current stdout to the file descriptor
		{
        	perror("Error redirecting output");
            exit(EXIT_FAILURE);
        }
		if (dup2(base->fd_in, 0) == -1) //change the current stdin to the file descriptor
		{
			// perror("Error redirecting input");
			exit(EXIT_FAILURE);
		}
		dprintf(base->ft_custom_exit, "%d\n", base->fd_out); // to remove
		execve(base->env_path, av, tab);
		free_tab(av);
		dprintf(base->ft_custom_exit, "ft_exec : execve failed\n");
		dup2(fd_tmp2, 0); // restore the current stdin
		dup2(fd_tmp, 1); // restore the current stdout
		close(base->fd_out); // if failed to execute, close the file descriptor
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	if (base->flag_redir == 1)
	{
		write(base->fd_out, "\n", 1);
		base->flag_redir = -1;
	}
	dup2(1, base->fd_out);
	dup2(0, base->fd_in);
	return (0);
}


int	ft_exec(char **av, char **tab, t_base *base)
{
	// int		tmp1;
	(void)base;

	int i = 1; // to remove

	ft_putstr_fd("in ft_exec\n", base->ft_custom_exit);
	dprintf(base->ft_custom_exit, "about to execute |"); // to remove
	while (av[i])	 // to remove
		dprintf(base->ft_custom_exit, "%s ", av[i++]); // to remove
	dprintf(base->ft_custom_exit, "|\n"); // to remove
	ft_spe_execve(av, tab, base);
	ft_putstr_fd("execute done\n", base->ft_custom_exit); // to remove
	dup2(1, base->fd_out);
	dup2(0, base->fd_in);
	return (0);
}

int ft_exec_prog(char **av, t_base *base)
{
	base->env_path = get_path_tab(av[0], base->env_old);
	//fp = get_path_tab(av[0], base->env_old);
	if(!base->env_path)
		return(0);
	if (base->env_path == NULL)
	{
		ft_putstr_fd("Failed to find executable\n", base->fd_out);
		return (0);
	}
	ft_exec(av, base->env_old, base);
	dup2(1, base->fd_out);
	dup2(0, base->fd_in);
	//perror("execve failed");
	return (1);
}
