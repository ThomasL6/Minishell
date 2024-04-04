/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <vamologl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:26:05 by vamologl          #+#    #+#             */
/*   Updated: 2024/04/04 15:41:05 by vamologl         ###   ########.fr       */
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
	(*idx)++; // pass the '$'
	if (s[(*idx)] && s[(*idx)] == '?')
	{
		(*idx)++; // pass the '?'
		// return("2"); // 	
		return (ft_itoa(base->return_value)); /* here */
	}
	i = (*idx);
	while (s[(*idx)] && s[(*idx)] != ' ' && s[(*idx)] != '\"'
	&& s[(*idx)] != '\'' && s[(*idx)] != ',')
		(*idx)++;
	ret = addsr(ret, &s[i], (*idx) - i);
	if (!ret)
		return (ft_strdup("$"));
	// return (get_env(ret, base)); /* here */
	return (prep_char_env(base, ret));
}



char *extract_quote(char *s, int *idx, t_base *base, const char quote) /* here */
{
	int		i;
	char	*ret;
	char	*dollar;

	(*idx)++; // pass the first quote
	ret = NULL;
	dollar = NULL;
	while ((*idx) < (int)ft_strlen(s) && s[(*idx)] != quote)
	{
		i = *idx; // to get the len
		while (s[(*idx)] != quote && !(s[(*idx)] == '$' && quote == '\"'))
			(*idx)++;
		ret = addsr(ret, &s[i], (*idx) - i); //add to ret for return value ?
		if (s[(*idx)] && s[(*idx)] != quote)
		{
			dollar = extract_dollar(s, idx, base); //extract the dollar if found /* here */
			ret = addsr(ret, dollar, ft_strlen(dollar)); // add true value to ret
			free(dollar); //free dollar after joining it with ret
		}
	}
	(*idx)++; // past the last quote
	return (ret);
}

char	*modif_token(char *s, t_base *base) /* here */
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
			special_str = extract_dollar(s, &i, base); /* here */
		else
			special_str = extract_quote(s, &i, base, s[i]); /* here */
		new_token = addsr(new_token, special_str, ft_strlen(special_str));
		if (!special_str)
			free(special_str);
		s = s + i;
	}
	return (new_token);
}
