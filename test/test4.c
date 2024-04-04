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
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen((char *)s) < start)
		return (ft_strdup(""));
	j = ft_strlen((char *)s + start);
	if (j < len)
		len = j;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_nbword(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

int	ft_lword(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	int		word;
	char	**strs;

	i = 0;
	j = -1;
	word = ft_nbword(s, c);
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		size = ft_lword(s, c, i);
		strs[j] = ft_substr(s, i, size);
		if (!strs[j])
			return (NULL);
		i += size;
	}
	strs[j] = 0;
	return (strs);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + \
		ft_strlen((char *)s2) + 1));
	i = 0;
	if (str != NULL)
	{
		while (*s1 != '\0')
		{
			str[i] = *s1;
			i++;
			s1++;
		}
		while (*s2 != '\0')
		{
			str[i] = *s2;
			i++;
			s2++;
		}
		str[i] = '\0';
	}
	return (str);
}

char	*ft_sstrndup(char *s, int n, int start)
{
	char	*dst;
	int		i;

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


int	nb_char(char *s)
{
	int	i;
	int	j;
	int	count;

	if (!s)
		return (0);
	i = 0;
	j = ft_strlen(s);
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

	len = nb_char(s);
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
	// free(s);
	return (dst);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == s2[i] && (unsigned char)s1[i] != '\0'
		&& s2[i] != '\0' && i < n - 1)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

char    *get_my_env(char *name, char **env)
{
    int        i;
    char    *ret;
    char    **str_env;

    i = 0;
    while (env[i])
    {
        str_env = ft_split(env[i], '=');
        if (str_env && ft_strncmp(name, str_env[0], ft_strlen(str_env[0])) == 0)
        {
            if (str_env[1] == NULL)
                continue ;
            ret = ft_strdup(str_env[1]);
            free_tab(str_env);
            return (ret);
        }
        i++;
        free_tab(str_env);
    }
    return (NULL);
}

/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*-----------------------------------------------*/

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}


/**/
char *get_env(char *cmp, char **env)
{
	int		i;
	char	*ret;
	char	**var;

	i = -1;
	ret = NULL;
	while (env && env[++i])
	{
		var = ft_split(env[i], '=');
		if (!var || !var[0])
			continue ;
		if (!ft_strcmp(var[0], cmp))
		{
			if (!var[1])
				ret = ft_strdup(""); // var=
			else
				ret = ft_strdup(var[1]);
			free_tab(var);
			break ;
		}
		free_tab(var);
	}
	free(cmp);
	return (ret);
}


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

char *extract_dollar(const char *s, int *idx, char **env) /* here */
{
	int		i;
	char *ret;

	ret = NULL;
	(*idx)++; // pass the '$'
	if (s[(*idx)] && s[(*idx)] == '?')
	{
		(*idx)++; // pass the '?'
		return("2"); // return (itoa(base->return_value)); /* here */
	}
	i = (*idx);
	while (s[(*idx)] && s[(*idx)] != ' ' && s[(*idx)] != '\"'
	&& s[(*idx)] != '\'' && s[(*idx)] != ',')
		(*idx)++;
	ret = addsr(ret, &s[i], (*idx) - i);
	if (!ret)
		return (ft_strdup("$"));
	return (get_env(ret, env)); /* here */
}



char *extract_quote(char *s, int *idx, char **env, const char quote) /* here */
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
			dollar = extract_dollar(s, idx, env); //extract the dollar if found /* here */
			ret = addsr(ret, dollar, ft_strlen(dollar)); // add true value to ret
			free(dollar); //free dollar after joining it with ret
		}
	}
	(*idx)++; // past the last quote
	return (ret);
}

char	*modif_token(char *s, char **env) /* here */
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
			special_str = extract_dollar(s, &i, env); /* here */
		else
			special_str = extract_quote(s, &i, env, s[i]); /* here */
		new_token = addsr(new_token, special_str, ft_strlen(special_str));
		if (!special_str)
			free(special_str);
		s = s + i;
	}
	return (new_token);
}


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	// char *s = "Bonjour michel et $? mark, '$martin', $jacky \"$USER\" et $SHLVL sont la\0";
	// char *s = "test  \"al\'p\'ha\" end\0";
	char *s = "$? salut \"\'$U\'\" michel $SHLVL,654 \"$USER\", \'$USER\' et \"$U\'S\'E\'R\" dwads\0";
	printf("Before -> %s\n", s);
	char *to_free = modif_token(s, env);
	printf("After  -> %s\n", to_free);
	free(to_free);
	return (0);
}
