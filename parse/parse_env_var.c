/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <vamologl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:26:05 by vamologl          #+#    #+#             */
/*   Updated: 2024/04/05 11:58:20 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*addsr(char *origin, const char *to_add, size_t n)
{
	size_t	i;
	int		idx;
	char	*ret;

	i = 0;
	idx = 0;
	if (!origin && n == 0)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(origin) + n + 1));
	if (!ret)
		return (NULL);
	while (origin && origin[i])
		ret[idx++] = origin[i++];
	i = 0;
	while (i < n)
		ret[idx++] = to_add[i++];
	ret[idx] = 0;
	if (!origin)
		free(origin);
	return (ret);
}

char *prep_char_env(t_base *base, char *s)
{
	char *ret;
	char *tmp;

	tmp = ft_strjoin(s, "=");
	free(s);
	ret = get_var_env(base->env, tmp);
	free(tmp);
	return (ret);
}

char *extract_dollar(const char *s, int *idx, t_base *base)
{
	int		i;
	char *ret;

	ret = NULL;
	(*idx)++;
	if (s[(*idx)] && s[(*idx)] == '?')
	{
		(*idx)++;	
		return (ft_itoa(base->return_value));
	}
	i = (*idx);
	while (s[(*idx)] && s[(*idx)] != ' ' && s[(*idx)] != '\"'
	&& s[(*idx)] != '\'' && s[(*idx)] != ',')
		(*idx)++;
	ret = addsr(ret, &s[i], (*idx) - i);
	if (!ret)
		return (ft_strdup("$"));
	ret = prep_char_env(base, ret);
	return (ret);
}



char *extract_quote(char *s, int *idx, t_base *base, const char quote) 
{
	int		i;
	char	*ret;
	char	*dollar;

	(*idx)++;
	ret = NULL;
	dollar = NULL;
	while ((*idx) < (int)ft_strlen(s) && s[(*idx)] != quote)
	{
		i = *idx;
		while (s[(*idx)] != quote && !(s[(*idx)] == '$' && quote == '\"'))
			(*idx)++;
		ret = addsr(ret, &s[i], (*idx) - i);
		if (s[(*idx)] && s[(*idx)] != quote)
		{
			dollar = extract_dollar(s, idx, base);
			ret = addsr(ret, dollar, ft_strlen(dollar));
			free(dollar);
		}
	}
	(*idx)++;
	return (ret);
}

char	*modif_token(char *s, t_base *base) 
{
	int		i;
	char	*special_str;
	char	*new_token;

	new_token = NULL;
	if (!s)
		return (NULL);
	while (ft_strlen(s) > 0)
	{
		i = 0;
		while (s[i] && s[i] != '\"' && s[i] != '\'' && s[i] != '$')
			i++;
		new_token = addsr(new_token, s, i);
		if (!s[i])
			break ;
		if (s[i] == '$')
			special_str = extract_dollar(s, &i, base);
		else
			special_str = extract_quote(s, &i, base, s[i]);
		new_token = addsr(new_token, special_str, ft_strlen(special_str));
		if (special_str)
			free(special_str);
		s = s + i;
	}
	return (new_token);
}
