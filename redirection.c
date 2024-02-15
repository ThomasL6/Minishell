/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:51:32 by thlefebv          #+#    #+#             */
/*   Updated: 2024/02/13 09:51:34 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	fd_write(int fd, char *str, int flag)
// {
// 	write(fd, str, strlen(str));
// 	if (flag == 1)
// 		write(fd, "\n", 1);
// 	return (strlen(str));
// }

// int main2(char **av, int fd, int flag)
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

// int	main(int ac, char **av)
// {
// 	int fd = -1;
// 	int flag = 0;

// 	if (ac <= 1)
// 		printf("Error - no input\n");
// 	if (atoi(av[1]) == 0)
// 		fd = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (atoi(av[1]) == 1)
// 		fd = open(av[2], O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	else
// 	{
// 		printf("Error - invalide mode\n");
// 		return (-3);
// 	}
// 	main2(av, fd, flag);
// }

int	ft_find_redirection(char const *s, int i)
{
	if (s[i] == '>' && s[i])
	{
		if (s[i + 1] == '>')
			return (2);
		return (1);
	}
	else if (s[i] == '<' && s[i])
	{
		if (s[i + 1] == '<')
			return (4);
		return (3);
	}
	return (0);
}
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
            fd = open(str + i + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
            fd = open(str + i + 2, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
    return 0;
}


int main(void)
{
	t_base base;
	base.input = "commande > fichier.txt"; // exemple d'entrée avec redirection

	if (ft_redir(&base) == -1)
	{
		fprintf(stderr, "Redirection failed\n");
		exit(EXIT_FAILURE);
	}

	// Votre code pour exécuter la commande avec redirection ici

	return (0);
}