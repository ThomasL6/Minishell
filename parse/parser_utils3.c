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

int	is_there_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
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
		ret[l++] = tmp[i++];
	ret[l] = '\0';
	ret = get_var_env(base->env, ft_strjoin(ret, "="));
	if (ret != NULL)
		base->tableau[m][j] = ft_strdup(ret);
	free(tmp);
	free(ret);
}

void	get_input_tab2(t_base *base, int i, int j)
{
	while (base->tableau[i][j])
	{
		if (base->tableau[i][j][0] != '\'')
		{
			if (is_there_char(base->tableau[i][j], '$') != 0)
			{
				if (ft_strncmp(base->tableau[i][j], "$?", 2) == 0)
					base->tableau[i][j] = ft_strdup
						(ft_itoa(base->return_value));
				// else
					// gest_dollar(base, j, i);
			}
		}
		else if (base->tableau[i][j][0] == '\'')
			base->tableau[i][j] = remove_simple_quote(base->tableau[i][j]);
		j++;
	}
} 

void	get_input_tab(t_base *base, int i)
{
	int	j;

	j = 0;
	base->tableau[i] = ft_super_split(base->input);
	while (base->tableau[i][j])
	{
		base->tableau[i][j] = ft_strndup(base->tableau[i][j],
				nb_char(base->tableau[i][j]));
		j++;
	}
	j = 0;
	get_input_tab2(base, i, j);
}


