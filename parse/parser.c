/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:06:26 by vamologl          #+#    #+#             */
/*   Updated: 2024/01/23 11:06:28 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	int		i;
	char	*dst;

	len = ft_strlen((char *)s);
	i = 0;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	while (s[i])
	{
		if (dst[i] == ' ' && s[i + 1] == '\0')
			break;
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	nb_char(char *s)
{
	int i;
	int j;

	int	count;

	i = 0;
	j = strlen(s);
	j--;
	while ((s[j] == ' ' || s[j] == '\t') && j > 0)
		j--;
	if (j < 0)
		return (-1);
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	count = 0;
	while (i <= j)
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_strndup(const char *s, int n)
{
	size_t	len;
	int		i;
	char	*dst;

	len = nb_char((char *)s);
	i = 0;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	while (s[i] && i <= n)
	{
		if (s[i] == ' ' && s[i + 1] == '\0')
			break;
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
//	printf("|%ld|%s|\n",len, dst);
	return (dst);
}

void	get_input_tab(t_base *base)
{
	int i = -1; // to remove
	int	j;

	(void)i;
	(void)j;
	j = 0;
	base->tableau[0] = ft_super_split(base->input); // replaced ft_special_split, fuck you special split
	while (base->tableau[j])
	{
		//printf("%s\n", base->tableau[j]);
		base->tableau[0][j] = ft_strndup(base->tableau[0][j], nb_char(base->tableau[0][j]));
		j++;
	}
}

void	error(int i, t_base *base)
{
	if (i == 0)
	{
		ft_putstr_fd("Error -", 1);
		ft_putstr_fd(base->tableau[0][0], 1);
		ft_putstr_fd(" command not found\n", 1);
	}
	else if (i == 1)
	{
		ft_putstr_fd("exit not free'd\n", 1);
		exit_prog(0, base->env, base);
		exit(1273);
	}
}

void	fd_change(t_base *base)
{
	if (base->tableau[0][1] == NULL)
	{
		base->fd_out = 1;
		return ;
	}
	else if (base->tableau[0][2] != NULL)
	{
		dprintf(base->fd_out, "Error - too many arguments\n");
		dprintf(base->ft_custom_exit, "Error - too many arguments\n");
		return ;
	}
	else

		base->fd_out = open(base->tableau[0][1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	return ;
}

void	parser(t_base *base)
{
	get_input_tab(base);
	if (ft_strcmp("", base->tableau[0][0]) == 0)
		return ;
	else if (ft_strcmp("env", base->tableau[0][0]) == 0)
		print_list_env(base->env, base);
	else if (ft_strcmp("echo", base->tableau[0][0]) == 0)
		own_echo(base);
	else if (ft_strcmp("pwd", base->tableau[0][0]) == 0)
		get_pwd(base);
	else if (ft_strcmp("cd", base->tableau[0][0]) == 0)
		own_cd(base->input, base);
	else if (ft_strcmp("export", base->tableau[0][0]) == 0)
		ft_export(base);
	else if (ft_strcmp("unset", base->tableau[0][0]) == 0)
		ft_unset(base);
	else if (ft_strcmp("exit", base->tableau[0][0]) == 0)
		error(0, base);
	else if (ft_strcmp("fdchange", base->tableau[0][0]) == 0) // to remove
		fd_change(base); // to remove
	else if (!ft_exec_prog(base->tableau[0], base))
	{
		ft_putstr_fd("Error - command not found\n", base->fd_out);
		ft_putstr_fd(base->tableau[0][0], base->fd_out);
		ft_putchar_fd('\n', base->fd_out);
		// printf("Error - command %s not found\n", base->tableau[0][0]);
	}
	return ;
}

	//chaque "mot" dans un maillon [x]
	//changer les variables env en votre valeur ($PATH -> path dans votre env) [x]
	// -> exec [?]