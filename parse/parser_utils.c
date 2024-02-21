#include "../include/minishell.h"

int	check_quote(const char *s, int i, char c)
{
	int	len;

	len = 0;
	i++;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len + 1);
}

int	ft_find_redirection(char const *s, int i)
{
	if (s[i] == '>' && s[i])
	{
		if (s[i + 1] == '>')
			return (2);
		return (1);
	}
	else if (s[i] == '<' && s[i])
	{
		if (s[i + 1] == '<')
			return (4);
		return (3);
	}
	return (0);
}

int	where_is_equal(const char *s, int i) // return len before the char
{
	int start;

	start = i;
	while (s[i] != '=' && s[i] != '\0')
	{
		if (s[i] == '=')
			return (i - start);
		i++;
	}
	return (ft_strlen(s));
}

int	ft_special_lword(char const *s, int i)
{
	int	size;

	size = 0;
	if (s[i] == '>' || s[i] == '<')
		size = ft_find_redirection(s, i); 
	else if (s[i] == '\"' && s[i])
		size = check_quote(s, i, '\"');
	else if (s[i] == '\'' && s[i])
		size = check_quote(s, i, '\'');
	else if (s[i] == '=' && s[i])
	{
		printf("%d\n", size);
		size = where_is_equal(s, i);
	}
	else
		size = check_quote(s, i, ' ');
	return (size + 1);
}


char	**ft_special_split(char const *s)
{
	int		i;
	int		j;
	int		size;
	int		word;
	char	**strs;

	i = 0;
	j = -1;
	size = 0;
	word = countwords(s, 0, 0, 0);
	printf("word = %d\n", word);
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++j < word)
	{
		while (s[i] == ' ')
			i++;
		size = ft_special_lword(s, i);
		strs[j] = ft_substr(s, i, size);
		if (!strs[j])
			return (NULL);
		i += size;
		//printf("%s\n", strs[j]);
	}
	strs[j] = 0;
	return (strs);
}

int	ft_strlen_wo_quote(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

// input -> parser -> split -> base-tableau -> trim -> parser -> echo -> output

//		echo	|| tab[0]
//		"$PATH"	|| tab[1]
