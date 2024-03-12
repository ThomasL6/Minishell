#include "../include/minishell.h"

int	only_one_redir(char **s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_find_redirection(s[i]) != 0)
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

void ft_double_redir(char **av, t_base *base)
{
	int i;
	char **tmp;
	(void)av;
	
	i = -1;
	tmp = malloc(sizeof(char **)*(ft_tablen(base->tableau[0])));
	while (base->tableau[0][++i] && ft_strncmp(base->tableau[0][i], ">>", ft_strlen(base->tableau[0][i])) != 0)
	{
		if (!base->tableau[0][i + 1])
		{
			base->fd_out = 1;
			return ;
		}
		tmp[i] = base->tableau[0][i];
	}
	tmp[i] = NULL;
	if (!base->tableau[0][i + 1])
	{
		base->fd_out = 1;
		free(tmp);
		return ;
	}
	base->fd_out = open(base->tableau[0][++i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	base->flag_redir = 0;
}


void ft_basic_redir(char **av, t_base *base)
{
	int i;
	char **tmp;
	(void)av;

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
	base->fd_out = open(base->tableau[0][i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	base->flag_redir = 0;
}

int ft_left_redir(char **av, t_base *base)
{
	int i;
	char **tmp;
	(void)av;

	i = 0;
	tmp = malloc(sizeof(char **) * (ft_tablen(base->tableau[0])));
	while (ft_strncmp(base->tableau[0][i], "<", ft_strlen(base->tableau[0][i])) != 0 && base->tableau[0][i])
	{
		if (base->tableau[0][i + 1] == NULL)
		{
			base->fd_in = 0;
			return (1);
		}
		tmp[i] = base->tableau[0][i];
		i++;
	}
	tmp[i] = NULL;
	if (base->tableau[0][i + 1] == NULL)
	{
		base->fd_in = 0;
		free(tmp);
		return (1);
	}
	i++;
	base->fd_in = open(base->tableau[0][i], O_RDONLY , 0644);
	if (base->fd_in == -1)
	{
		perror(base->tableau[0][i]);
		return (-1);
	}
	base->flag_redir = 1;
	return (0);
}

void    child_routin(int pipefd[2], char *eof, char *buf)
{
	int nb;

	close(pipefd[0]);
	buf = malloc(sizeof(char **) + BUFFER_SZ);
	while (buf)
	{
		write(1, "> ", 2);
		nb = read(0, buf, BUFFER_SZ); //ft to strlen
		if (nb == -1)
		{
			perror("here_doc");
			continue ;
		}
		buf[nb - 1] = 0; // 0 = '/0'
		if (ft_strcmp(eof, buf) == 0)
			break ;
		write(pipefd[1], buf, ft_strlen(buf));
		write(pipefd[1], "\n", 1);
	}
	// write(STDOUT_FILENO, "reached the end\n", 16);
	free(buf);
	close(pipefd[1]);
	exit(0);
}

/* << */
int here_doc(char *eof, t_base *base)
{
	int pipefd[2];
	pid_t pid;
	char *buf;

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
	waitpid(pid, NULL, 0);

	return (pipefd[0]);
}


void ft_double_lredir(t_base *base)
{
	int i;

	i = 0;
	while (base->tableau[0][i] != NULL)
	{
		if (ft_strcmp(base->tableau[0][i], "<<") == 0)
		{
			dprintf(base->ft_custom_exit, "found <<\n");
			here_doc(base->tableau[0][i + 1], base);
		}
		i++;
	}
	dup2(base->fd_out, 1);
	dup2(base->fd_in, 0);
}
