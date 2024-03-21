/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:13:06 by thlefebv          #+#    #+#             */
/*   Updated: 2024/03/14 16:13:08 by thlefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	nb_char(char *s)
{
	int	i;
	int	j;
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

char	*ft_strndup(char *s, int n)
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
			break ;
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	free(s);
	return (dst);
}

void	ft_print_triple_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			printf("%s\n", tab[i][j]);
			j++;
		}
		i++;
	}
}

int		is_there_char(char *s, char c)
{
	int i = 0;

	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return(1);
		i++;
	}
	return (0);
}

char *ft_sstrndup(char *s, int n, int start)
{
    int     i;
    char    *dst;

    i = 0;
    dst = (char *)malloc(sizeof(char) * (n + 1));
    if (!dst)
        return (0);
    while (s[start] && i < n)
    {
        dst[i] = s[start + i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

int		ft_strlen_dollar(char *s)
{
	int i;

	i = 0;
	while(s[i] && s[i] != '$')
	{
		if (s[i + 1] != '\0')
			return (i + 1);
		i++;
	}
	i++;
	while (s[i] && s[i] != '\"')
		i++;
	return (i);
}

void	gest_dollar(t_base *base, int j, int m)
{
	char	*tmp;
	char	*ret;
	int		i;
	int		k;
	int		l;
	
	i = 0;
	k = 0;
	l = 0;
	tmp = base->tableau[m][j];
	while (tmp[i] && tmp[i] != '$')
		i++;
	i++;
	k = i;
	while (tmp[k] && tmp[k] != '\0' && tmp[k] != '"' && tmp[k] != '\'')
		k++;
	ret = malloc(sizeof(char *) * (k - i) + 1);
	while (i < k)
	{
		ret[l] = tmp[i];
		l++;
		i++;
	}
	ret[l] = '\0';
	ret = get_var_env(base->env, ft_strjoin(ret, "="));
	if (ret != NULL)
		base->tableau[m][j] = ft_strdup(ret);
	free(tmp);
	free(ret);
}

char	*remove_simple_quote(char *s)
{
	char *ret;
	int i;
	int j;

	j = 0;
	i = 1;
	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * ft_strlen(s) - 1);
	if (!ret)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\'')
	{
		ret[j] = s[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}


void	get_input_tab(t_base *base, int i)
{
	int	j;

	j = 0;
	base->tableau[i] = ft_super_split(base->input);
	while (base->tableau[i][j])
	{
		base->tableau[i][j] = ft_strndup(base->tableau[i][j], nb_char(base->tableau[i][j]));
		j++;
	}
	j = 0;
	while (base->tableau[i][j])
	{
		if (base->tableau[i][j][0] != '\'')
		{
			if (is_there_char(base->tableau[i][j], '$') != 0)
			{
				if (ft_strncmp(base->tableau[i][j], "$?", 2) == 0)
					base->tableau[i][j] = ft_strdup(ft_itoa(base->return_value));
				else
					gest_dollar(base, j, i);
			}
		}
		else if (base->tableau[i][j][0] == '\'')
			base->tableau[i][j] = remove_simple_quote(base->tableau[i][j]);
		j++;
	}
}

int	no_command(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_find_redirection(av[i]) != 0)
			i += 2;
		else
			return (0);
	}
	return (1);
}
