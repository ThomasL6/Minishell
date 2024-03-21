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


int	correct_redirection_len(char *av)
{
	char *ret;
	int i;
	int j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * 4096);
	while (av[i])
	{
		if (av[i] == '>' || av[i] == '<')
		{
			ret[j++] = ' ';
			while (av[i] == '>' || av[i] == '<')
				ret[j++] = av[i++];
			ret[j++] = ' ';
		}
		else
			ret[j++] = av[i++];
	}
	free(ret);
	return (j);
}

char *correct_redirection(char *av)
{
	char *ret;
	int i;
	int j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * 4096);
	while (av[i])
	{
		if (av[i] == '>' || av[i] == '<')
		{
			ret[j++] = ' ';
			while (av[i] == '>' || av[i] == '<')
				ret[j++] = av[i++];
			ret[j++] = ' ';
		}
		else
			ret[j++] = av[i++];
	}
	return (ret);
}

char *correct_input_for_parser(char *s)
{
	char *str;
	char *tmp;
	int i = 0;
	int j = 0;

	tmp = correct_redirection(s);
	str = malloc(sizeof(char) * correct_redirection_len(s) + 1);
	while (i < correct_redirection_len(s) && tmp[i] != '\0')
	{
		if ((tmp[0] == ' ' || tmp[0] == '\t') && i == 0 && j == 0)
			i++;
		str[j] = tmp[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(tmp);
	return (str);
}

int main(int ac, char **av)
{
	char *str;

	if (!av[1])
		return (-1);
	str = correct_input_for_parser(av[1]);
	printf("str |%s|\nlen |%lu|\n", str, strlen(str));
	printf("len |%d|\n", correct_redirection_len(av[1]));
	return (1);
}

