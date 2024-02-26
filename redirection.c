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

#include "include/minishell.h"

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

// int	ft_find_redirection(char const *s, int i)
// {
// 	if (s[i] == '>' && s[i])
// 	{
// 		if (s[i + 1] == '>')
// 			return (2);
// 		return (1);
// 	}
// 	else if (s[i] == '<' && s[i])
// 	{
// 		if (s[i + 1] == '<')
// 			return (4);
// 		return (3);
// 	}
// 	return (0);
// }
// int ft_redir(t_base *base)
// {
//     char *str;
//     int fd;
//     int i;
//     int symb;

//     // Initialisation
//     i = 0;
//     str = base->input;

//     // Trouver le type de redirection
//     symb = ft_find_redirection(str, i);

//     // Parcourir la chaîne pour trouver la redirection
//     while (str[i])
//     {
//         if (symb == 1 || symb == 2)
//         {
//             // Extraire la commande et les arguments
//             char *command = strdup(str); // Dupliquer la chaîne pour la manipulation
//             char *token = strtok(command, " "); // Diviser la chaîne en tokens

//             // Exécuter la commande avec execvp
//             if (execvp(token, &str) == -1)
//             {
//                 perror("Error executing command");
//                 free(command);
//                 return (-1);
//             }

//             // Libérer la mémoire allouée pour la duplication de la chaîne
//             free(command);
            
//             // Ouvrir le fichier en fonction du type de redirection
//             if (symb == 1)
//                 fd = open(str + i + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Redirection >
//             else if (symb == 2)
//                 fd = open(str + i + 2, O_WRONLY | O_CREAT | O_APPEND, 0644); // Redirection >>
            
//             // Vérifier l'ouverture du fichier
//             if (fd == -1)
//             {
//                 perror("Error opening file");
//                 return (-1);
//             }

//             // Rediriger stdout vers le fichier
//             if (dup2(fd, STDOUT_FILENO) == -1)
//             {
//                 perror("Error redirecting stdout");
//                 close(fd);
//                 return (-1);
//             }

//             // Fermer le descripteur de fichier du fichier ouvert
//             close(fd);

//             // Arrêter la recherche de redirections après avoir trouvé une redirection
//             break;
//         }
//         i++;
//     }

//     return 0;
// }


// int main(void)
// {
// 	t_base base;
// 	base.input = "commande > fichier.txt"; // exemple d'entrée avec redirection

// 	if (ft_redir(&base) == -1)
// 	{
// 		fprintf(stderr, "Redirection failed\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	// Votre code pour exécuter la commande avec redirection ici

// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// Fonction de redirection de la sortie de la commande vers un fichier
void execute_with_redirection(char *command, char *output_file, char *redirection_symbol) {
    // Créer un processus enfant
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processus enfant
        
        // Ouvrir le fichier de sortie
        int fd;
        if (strcmp(redirection_symbol, ">") == 0) {
            fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Redirection >
        } else if (strcmp(redirection_symbol, ">>") == 0) {
            fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644); // Redirection >>
        } else {
            fprintf(stderr, "Invalid redirection symbol: %s\n", redirection_symbol);
            exit(EXIT_FAILURE);
        }
        
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        
        // Rediriger stdout vers le fichier
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            close(fd);
            exit(EXIT_FAILURE);
        }
        
        // Fermer le descripteur de fichier
        close(fd);
        
        // Exécuter la commande
        execlp(command, command, NULL);
        
        // Si execlp retourne, cela signifie qu'il y a eu une erreur
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Processus parent
        // Attendre que le processus enfant se termine
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char *argv[]) {
    // Vérifier le nombre d'arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <command> <redirection_symbol> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Appeler la fonction de redirection avec les arguments spécifiés
    execute_with_redirection(argv[1], argv[3], argv[2]);
    
    return 0;
}
