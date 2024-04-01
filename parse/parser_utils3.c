/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <vamologl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:13:06 by thlefebv          #+#    #+#             */
/*   Updated: 2024/04/01 15:55:44 by vamologl         ###   ########.fr       */
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


char	*is_token_env(char *s, t_base *base)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(s, "=");
	printf("tmp = [%s]\n", tmp);
	tmp2 = get_var_env(base->env, tmp);
	free(tmp);
	if (!s)
		return (NULL);
	free(s);
	return (tmp2);	
}

char *extract_dollar(char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] == '\0')
		return (NULL);
	i++;
	while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
	{
		i++;
		j++;
	}
	ret = ft_sstrndup(s, j, i - j);
	return (ret);
}

char	*remove_dollard_token(char *s)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != ' ')
		i++;
	ret = malloc(sizeof(char) * (ft_strlen(s) - i) + 1);
	while (s[i])
	{
		ret[j] = s[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	free(s);
	return (ret);
}

int verify_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*gest_dollar(char *s, t_base *base)
{
	char	*ret;
	char	**tmp;
	char	*extracted;
	char	*tmp2;

	ret = NULL;
	tmp2 = NULL;
	if (verify_dollar(s) == 0)
		return (s);
	if (s[0] == '$')
	{
		ret = extract_dollar(s);
		ret = is_token_env(ret, base);
		return (ret);
	}
	tmp = ft_split(s, '$');
	if (!tmp)
		return (NULL);
	tmp[1] = remove_dollard_token(tmp[1]);
	extracted = extract_dollar(s);
	extracted = is_token_env(extracted, base);
	if (!extracted)
	{
		ret = ft_strjoin(tmp[0], tmp[1]);
	}
	else
	{
		tmp2 = ft_strjoin(tmp[0], extracted);
		ret = ft_strjoin(tmp2, tmp[1]);
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	free(tmp2);
	return (ret);
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
				else
				{
					base->tableau[i][j] = gest_dollar(base->tableau[i][j], base);
				}
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


