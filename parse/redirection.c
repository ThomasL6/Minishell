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
int ft_redir(t_base *base)
{
	char	*str;
	int		fd;
	int		i;
	int		symb;

	i = 0;
	str = base->input;
	symb = ft_find_redirection(&str[i], i);
	while(str[i])
	{
		if(symb == 1)
		{
			fd = open(str + i + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("Error opening file");
				return(-1);
			}
			while(str[i] && str[i] != ' ')
				i++;
		}
 		else if (symb == 2)
        {
            fd = open(str + i + 2, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (fd == -1)
            {
				perror("Error opening file for writing");
                return (-1);
            }
         	while (str[i] && str[i] != ' ')
                i++;
        }
        else
            i++;
    }
    return 0;
}
