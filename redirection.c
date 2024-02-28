// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/02/19 11:25:18 by vamologl          #+#    #+#             */
// /*   Updated: 2024/02/19 11:25:28 by vamologl         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "include/minishell.h"
// void	free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab && tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

// char	*get_my_env(char *name, char **env)
// {
// 	int		i;
// 	char	*ret;
// 	char	**str_env;

// 	i = 0;
// 	while (env[i])
// 	{
// 		str_env = ft_split(env[i], '=');
// 		if (str_env && ft_strncmp(name, str_env[0], ft_strlen(str_env[0])) == 0)
// 		{
// 			if (str_env[1] == NULL)
// 				continue ;
// 			ret = ft_strdup(str_env[1]);
// 			free_tab(str_env);
// 			return (ret);
// 		}
// 		i++;
// 		free_tab(str_env);
// 	}
// 	return (NULL);
// }


// static char    *build_exec_path(char *path, char *cmd)
// {
//     char    *exec_path;
//     char    *tmp;

//     exec_path = ft_strjoin(path, "/");
//     tmp = exec_path;
//     exec_path = ft_strjoin(exec_path, cmd);
//     free(tmp);
//     return (exec_path);
// }

// char    *get_path_tab(char *input, char **env)
// {
//     char    **path;
//     char    **s_cmd;
//     char    *exec_path;
//     int        i;

//     if (access(input, F_OK | X_OK) == 0)
//         return (ft_strdup(input));
//     path = ft_split(get_my_env("PATH=", env), ':');
//     s_cmd = ft_split(input, ' ');
//     i = 0;
//     while (path && path[i])
//     {
//         exec_path = build_exec_path(path[i], s_cmd[0]);
//         if (access(exec_path, F_OK | X_OK) == 0)
//         {
//             free_tab(s_cmd);
//             free_tab(path);
//             return (exec_path);
//         }
//         free(exec_path);
//         i++;
//     }
//     free_tab(s_cmd);
//     free_tab(path);
//     return (NULL);
// }
// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i = 0;

// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			break;
// 		i++;
// 	}
// 	return (s1[i] - s2[i]);
// }

// int	ft_find_redirection(char *s)
// {
// 	if (ft_strcmp(s, ">") == 0)
// 		return (1);
// 	else if (ft_strcmp(s, ">>") == 0)
// 		return (2);
// 	else if (ft_strcmp(s, "<") == 0)
// 		return (3);
// 	else if (ft_strcmp(s, "<<") == 0)
// 		return (4);
// 	return (0);
// }


// int	ft_exec(char *fp, char **av, char **env)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	if (pid == 0)
//         if (env)
// 		    execve(fp, av, env);
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }

// int ft_redir(char **argv, int argc)
// {
//     int fd;
//     int symb;

//     symb = ft_find_redirection(argv[2]);
// 	if (symb == 1 || symb == 2)
// 	{
// 		if (symb == 1)
// 			fd = open(argv[3] , O_WRONLY | O_CREAT | O_TRUNC, 0644); // changer le 3 par une variable qui trouve le nom du fichier ( arg apres la redir)
// 		else if (symb == 2)
// 			fd = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			perror("Error opening file");
// 			return (-1);
// 		}
// 		dup2(fd, STDOUT_FILENO);
// 		execve;
// 		dup2(STDOUT_FILENO, 1);
// 		close(fd);
// 	}
//     return 0;
// }


// int main(int arc, char **arv)
// {
// 	char *argv[] = {"./a.out", arv[1], arv[2], arv[3]};
// 	int argc = 3;

// 	if (ft_redir(argv, argc) == -1)
// 	{
// 		fprintf(stderr, "Redirection failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }

