// #include "include/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/*---------------------------------------------------------*/

int	fd_write(int fd, char *str, int flag)
{
	write(fd, str, strlen(str));
	if (flag == 1)
		write(fd, "\n", 1);
	return (strlen(str));
}

int main2(char **av, int fd, int flag)
{
	if (atoi(av[1]) && fd && read(fd, NULL, 1) <= 1)
		flag = 1; // if file is empty
	if (fd == -1)
	{
		printf("Error - file not found\n");
		return (-1);
	}
	else if (av[3])
	{
		fd_write(fd, av[3], flag);
		close(fd);
	}
	else
	{
		printf("Error - no text to write\n");
		return (-2);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int fd = -1;
	int flag = 0;

	if (ac <= 1)
		printf("Error - no input\n");
	if (atoi(av[1]) == 0)
		fd = open(av[2], O_WRONLY | O_CREAT, 0640);
	else if (atoi(av[1]) == 1)
		fd = open(av[2], O_WRONLY | O_APPEND | O_CREAT, 0640);
	else
	{
		printf("Error - invalide mode\n");
		return (-3);
	}
	main2(av, fd, flag);
}

/*---------------------------------------------------------*/


// int	main(void)
// {
// 	pid_t pid;
// 	int	i = 0;

// 	printf("Fork test\n");
// 	pid = fork();
// 	if (pid == -1) // check if pid fork is not -1, bc if -1 then error
// 		return (-1);
// 	printf("%d - Fork is in fact alive\n", pid);
// 	i = 0;
// 	while (pid == 0 && i < 100)
// 	{
// 		char *s = malloc(sizeof(char *) + 1);
// 		s = "a";
// 		pid = fork();
// 			if (pid == 0)
// 				printf("test child of child\n");
// 		printf("child proces is %d\n", pid);
// 		i++;
// 	}
// 	if (pid > 0)
// 		printf("original proces %d\n", pid);
// 	return (0);
// }