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

int	is_there_redir(char **s)
{
	int	i;

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

int	ft_spe_execve2(char **av, char **tab, t_base *base)
{
	int	fd_tmp;
	int	fd_tmp2;

	fd_tmp = dup(1);
	fd_tmp2 = dup(0);
	if (dup2(base->fd_out, 1) == -1)
	{
		perror("Error redirecting output");
		exit(EXIT_FAILURE);
	}
	if (dup2(base->fd_in, 0) == -1)
	{
		perror("Error redirecting input");
		exit(EXIT_FAILURE);
	}
	base->return_value = execve(base->env_path, av, tab);
	free_tab(av);
	dup2(fd_tmp2, 0);
	dup2(fd_tmp, 1);
	close(base->fd_out);
	close(base->fd_in);
	exit(EXIT_FAILURE);
}

int	ft_spe_execve(char **av, char **tab, t_base *base)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		ft_spe_execve2(av, tab, base);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			base->return_value = WEXITSTATUS(status);
	}
	if (base->flag_redir == 1)
		base->flag_redir = -1;
	dup2(1, base->fd_out);
	dup2(0, base->fd_in);
	return (0);
}

int	ft_exec(char **av, char **tab, t_base *base)
{
	ft_spe_execve(av, tab, base);
	dup2(base->terminal_in, base->fd_out);
	dup2(base->terminal_out, base->fd_in);
	return (0);
}

int	ft_exec_prog(char **av, t_base *base)
{
	base->env_path = get_path_tab(av[0], base->env_old);
	if (!base->env_path)
		return (0);
	if (base->env_path == NULL)
	{
		ft_putstr_fd("Failed to find executable\n", base->fd_out);
		free(base->env_path);
		return (0);
	}
	ft_exec(av, base->env_old, base);
	free(base->env_path);
	dup2(1, base->fd_out);
	dup2(0, base->fd_in);
	return (1);
}
