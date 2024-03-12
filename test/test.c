/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:24:50 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/19 11:24:54 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "include/minishell.h"
#include <string.h> //
#include <stddef.h>
#include <stdio.h> //
#include <stdlib.h> //
#include <unistd.h> //
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //
#include <dirent.h>
#include <sys/types.h> //
#include <sys/wait.h> //
#include <stdbool.h>


/**/

// int here_doc(char *eof)
// {
// 	char *s;

// 	while (1)
// 	{
// 		s = malloc(sizeof(char *) + strlen(eof) + 1);
// 		if (s)
// 			read(1, s, strlen(eof)); //ft to strlen
// 		if (strncmp(eof, s, strlen(eof) + 15) == 0 && s)
// 		{
// 			free(s);
// 			break ;
// 		}
// 		free(s);
// 	}
// 	write(1, "Reached the end\n", 16);

/*
char    **get_exec(char **tab)
{
	int i;
	int j;
    int k;
    char **ret;

	if (!tab)
		return (NULL);
    i = 0;
	while (tab[i])
	{
		if (ft_find_redirection(tab[i]) != 0 && tab[i])
			i += 2;
		else
			break;
	}
	j = i;
	while (ft_find_redirection(tab[j]) == 0 && tab[j])
		j++;
    k = 0;
    ret = (char **)malloc(sizeof(char *) * (j - i + 1));
	while (i < j)
	{
        ret[k] = strdup(tab[i]);
		i++;
        k++;
	}
    ret[k] = NULL;
    return (ret);
}

int	main(void)
{
	char *s;
	char **tab;
	int i;

	while (1)
	{
		i = 0;
		s = readline("--test-file-- ~$ ");
		if (s == NULL)
			break ;
		printf("%s\n", s);
		tab = ft_super_split(s);

        // test function under here
		tab = get_exec(tab);


        while (tab[i])
        {
            printf("tab[%d] = %s\n", i, tab[i]);
            i++;
        }
        if (!s)
            free(s);
	}
}*/

#define BUFFER_SZ 4096

void    child_routin(int pipefd, char *eof)
{
	char *buf;
	int nb;

	close(pipefd[0]);
	buf = malloc(sizeof(char **) + BUFFER_SZ);
	while (buf)
	{
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

int here_doc(char *eof)
{
	int pipefd[2];
	pid_t pid;

	buf = NULL;
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
        child_routin();
	}
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	return (pipefd[0]);
}

int main(int ac, char **av)
{
	int i = 1;

	if (ac < 2)
		return (1);
	while (av[i])
	{
		int	fd = 0;
		char buf[BUFFER_SZ] = { 0 };

		fd = here_doc(av[i]);

		read(fd, buf, BUFFER_SZ);
		dprintf(1, "{%s}\n", buf);
		i++;
	}
	return (0);
}
