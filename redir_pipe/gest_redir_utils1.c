/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_redir_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:22:07 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/14 16:22:08 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	only_one_type_redir(char **tab)
{
	int	i;
	int	tmp_redir;

	i = 0;
	tmp_redir = -1;
	while (tab[i] && tmp_redir == -1)
	{
		if (ft_find_redirection(tab[i]) == 1)
			tmp_redir = 1;
		else if (ft_find_redirection(tab[i]) == 2)
			tmp_redir = 2;
		else if (ft_find_redirection(tab[i]) == 3)
			tmp_redir = 3;
		i++;
	}
	while (tab[i])
	{
		if (ft_find_redirection(tab[i]) != 0
			&& ft_find_redirection(tab[i]) != tmp_redir)
			return (0);
		i++;
	}
	return (1);
}

int	here_doc(char *eof, t_base *base)
{
	char	*buf;
	pid_t	pid;
	int		pipefd[2];

	(void)base;
	buf = NULL;
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_routin(pipefd, eof, buf);
	close(pipefd[1]);
	base->return_value = waitpid(pid, NULL, 0);
	return (pipefd[0]);
}

void	child_routin(int pipefd[2], char *eof, char *buf)
{
	int	nb;

	close(pipefd[0]);
	buf = malloc(sizeof(char **) + BUFFER_SZ);
	while (buf)
	{
		write(1, "> ", 2);
		nb = read(0, buf, BUFFER_SZ);
		if (nb == -1)
		{
			perror("here_doc");
			continue ;
		}
		buf[nb - 1] = 0;
		if (ft_strcmp(eof, buf) == 0)
			break ;
		write(pipefd[1], buf, ft_strlen(buf));
		write(pipefd[1], "\n", 1);
	}
	free(buf);
	close(pipefd[1]);
	exit(0);
}
