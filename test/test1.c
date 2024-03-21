// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/02/19 11:24:50 by vamologl          #+#    #+#             */
// /*   Updated: 2024/02/19 11:24:54 by vamologl         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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

#define BUFFER_SIZE 128

typedef struct	s_test
{
	int pipefd[2];

	int		term_in;
	int 	term_out;
	char	**input;
	char	**env;
	char	*string;

    int    loc_pipe;
}				t_test	;

// ///---------------------------------------------------------------------------------------------///
// ///---------------------------------------------------------------------------------------------///
// ///---------------------------------------------------------------------------------------------///

// int ft_super_countwords(const char *s)
// {
//     int count = 0;
//     int inside_word = 0;
// 	int i;

// 	i = 0;
//     while (s[i])
//     {
//         if (s[i] == ' ' && s[i])
//             inside_word = 0;
//         else if (inside_word == 0)
//         {
//             inside_word = 1;
//             count++;
//         }
//         i++;
//     }
//     return (count);
// }

// const char *ft_skip_spaces(const char *s)
// {
//     while (*s && *s == ' ')
//         s++;
//     return s;
// }

// int ft_get_word_size(const char *s)
// {
//     int size = 0;
//     int insidequotes = 0;

//     while (s[size])
//     {
//         if (s[size] == '\"')
//             insidequotes = !insidequotes;
//         else if (s[size] == ' ' && !insidequotes)
//             break;
//         size++;
//     }
//     return size;
// }

// char *ft_extract_word(const char *s, int size)
// {
// 	int i;
//     char *word;

//     i = 0;
// 	word = (char *)malloc((size + 1) * sizeof(char));
// 	if (!word)
//         return NULL;
// 	while (i < size)
// 	{
// 		word[i] = s[i];
// 		i++;
// 	}
//     word[size] = '\0';
//     return (word);
// }

// char **ft_super_split(char const *s)
// {
//     int j = 0;
//     int word_count = ft_super_countwords(s);
//     char **strs = (char **)malloc((word_count + 1) * sizeof(char *));
//     if (!strs)
//         return NULL;

//     while (*s && j < word_count)
//     {
//         s = ft_skip_spaces(s);
//         int word_size = ft_get_word_size(s);
//         if (j > 0 && *(s - 1) == '=' && word_size == 0)
//             word_size++;
//         strs[j] = ft_extract_word(s, word_size);
//         if (!strs[j])
//         {
//             // Gestion d'erreur : libérer la mémoire allouée précédemment
//             for (int k = 0; k < j; k++)
//                 free(strs[k]);
//             free(strs);
//             return NULL;
//         }
//         j++;
//         s += word_size;
//     }
//     strs[j] = NULL;
//     return (strs);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	int		i;

// 	str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + \
// 		ft_strlen((char *)s2) + 1));
// 	i = 0;
// 	if (str != NULL)
// 	{
// 		while (*s1 != '\0')
// 		{
// 			str[i] = *s1;
// 			i++;
// 			s1++;
// 		}
// 		while (*s2 != '\0')
// 		{
// 			str[i] = *s2;
// 			i++;
// 			s2++;
// 		}
// 		str[i] = '\0';
// 	}
// 	return (str);
// }

// size_t ft_strlen(const char *str)
// {
// 	size_t i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// ///---------------------------------------------------------------------------------------------///
// ///---------------------------------------------------------------------------------------------///
// ///---------------------------------------------------------------------------------------------///

// int	find_pipe(t_test *test)
// {
// 	int i;

// 	i = 0;
// 	while (test->input[i])
// 	{
// 		if (strncmp(test->input[i], "|", 2) == 0)
// 		{
// 			test->loc_pipe = i;
// 			return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// void	writestr(int fd, const char *str)
// {
// 	write(fd, str, strlen(str));
// }

// void child0(t_test *test, char *buf)
// {
//     int	len = 0; // Current length of the string
//     int	bytes_read;
// 	int	buf_size = 256;

//     close(test->pipefd[1]);

//     buf = (char *)malloc(buf_size * sizeof(char));

//     if (buf == NULL) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }

//     while ((bytes_read = read(test->pipefd[0], buf + len, 1)) > 0) {
//         len += bytes_read;
//         if (len >= buf_size)
// 		{
//             buf_size *= 2; // Double the buffer size
//         	buf = (char *)realloc(buf, buf_size * sizeof(char));
//             if (buf == NULL)
// 			{
//                 perror("realloc");
//                 exit(EXIT_FAILURE);
//             }
//         }
//     }
//     if (bytes_read < 0) {
//         perror("read");
//         exit(EXIT_FAILURE);
//     }
//     buf[len] = '\0';

// 	int count = 0;
// 	len = 0;
// 	while (buf[len])
// 	{
// 		if (buf[len] == test->input[test->loc_pipe + 1][0])
// 			count++;
// 		len++;
// 	}
// 	printf("buf = %s\nthere is %d %c in the str", buf, count, test->input[test->loc_pipe + 1][0]);

//     close(test->pipefd[0]);
//     exit(EXIT_SUCCESS);
// }

// void	child1(t_test *test, char *av)
// {
// 	int i;
// 	int count = 0;
	
// 	i= 0;
// 	close(test->pipefd[0]);
// 	while (av[i] && av[i] != '|')
// 	{
// 		dprintf(test->pipefd[1],"%c", av[i]);
// 		i++;
// 	}
// 	// writestr(test->pipefd[1], av);
// 	close(test->pipefd[1]);
// 	wait(NULL);
// 	exit(EXIT_SUCCESS);
// }

// void ft_fork(t_test *test)
// {
// 	pid_t	pid;
// 	char	buf;
	
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (pipe(test->pipefd) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		else if (pid == 0)
// 		{
// 			child0(test, &buf); // read the string
// 			// exit(EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			child1(test, test->string); // write the string
// 			// exit(EXIT_SUCCESS);
// 		}
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		// exit(EXIT_SUCCESS);
// 	}
// }


// void	loop(t_test *test)
// {
// 	int i;

// 	i = 0;
// 	if (find_pipe(test) == -1)
// 	{
// 		printf("no pipe\n");
// 		while (test->input[i])
// 		{
// 			printf("input[%d] = %s\n", i, test->input[i]);
// 			free(test->input[i]);
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		printf("pipe\n");
// 		test->string = ft_strjoin(test->input[0], " ");
// 		i = 1;
// 		while (test->input[i])
// 		{
// 			test->string = ft_strjoin(test->string, test->input[i]);
// 			test->string = ft_strjoin(test->string, " ");
// 			free(test->input[i]);
// 			i++;
// 		}
// 		if (test->input[i] != NULL)
// 			free(test->input[i]);
// 		ft_fork(test);
// 	}
// }

// int	main(void)
// {
// 	t_test	*test;
// 	test = (t_test *)malloc(sizeof(t_test));

// 	test->string = NULL;
// 	test->input = NULL;
// 	while (1)
// 	{
// 		test->input = ft_super_split(readline("- test file -$ "));
// 		if (test->input[0] == NULL)
// 			continue ;
// 		if (strncmp(test->input[0], "exit", 4) == 0)
// 			break ;
// 		loop(test);
// 	}
// 	if (test->input)
// 		free(test->input);
// 	if (test->string)
// 		free(test->string);
// 	free(test);
// }

void execute_pipeline(char ***commands, int num_commands)
{
    int i;
    int pipefd[2];
    pid_t pid;

    int prev_pipe_read = STDIN_FILENO;

    for (i = 0; i < num_commands; i++)
    {
        if (i < num_commands - 1)
        {
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {  // Child process
            if (i < num_commands - 1)
            {
                // Redirect output to the write end of the pipe
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(pipefd[0]); // Close read end of pipe in child
            }

            // Redirect input from the previous command's output
            if (i != 0)
            {
                if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Execute command
            execvp(commands[i][0], commands[i]); // check command (parse thingy)
            perror("execvp");
            exit(EXIT_FAILURE);
        } 
        else 
        {  // Parent process
            wait(NULL); // Wait for child to finish

            if (i < num_commands - 1)
            {
                close(pipefd[1]); // Close write end of pipe in parent
                prev_pipe_read = pipefd[0];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    char **args = (char **)malloc(2 * sizeof(char *));
    char ***commands = (char ***)malloc(num_commands * sizeof(char **));
    int num_commands = argc - 1;
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command1> [<command2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (commands == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < num_commands; i++)
    {
        if (args == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        args[0] = argv[i + 1];
        args[1] = NULL;
        commands[i] = args;
    }

    execute_pipeline(commands, num_commands);

    // Free memory
    for (i = 0; i < num_commands; i++)
    {
        free(commands[i]);
    }
    free(commands);

    return 0;
}
