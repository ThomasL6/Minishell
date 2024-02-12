#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

// int ft_strlen(char *s)
// {
// 	int i = 0; 

// 	while (s[i] != '\0') 
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	int		i;

// 	str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + \
// 		ft_strlen((char *)s2) + 1));
// 	i = 0;
// 	if (str != NULL)
// 	{
// 		while (*s1 != '\0')
// 		{
// 			str[i] = *s1;
// 			i++;
// 			s1++;
// 		}
// 		while (*s2 != '\0')
// 		{
// 			str[i] = *s2;
// 			i++;
// 			s2++;
// 		}
// 		str[i] = '\0';
// 	}
// 	return (str);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*str;

// 	if (!s)
// 		return (NULL);
// 	if (strlen((char *)s) < start)
// 		return (strdup(""));
// 	j = strlen((char *)s + start);
// 	if (j < len)
// 		len = j;
// 	str = (char *)malloc((len + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = s[start + i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// int	ft_old_nbword(char const *s)
// {
// 	int	i;
// 	int	word;

// 	i = 0;
// 	word = 0;
// 	while (s && s[i])
// 	{
// 		if (s[i] != ' ')
// 		{
// 			word++;
// 			while (s[i] != ' ' && s[i])
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (word);
// }

// int	ft_lword(char const *s, int i, int option)
// {
// 	int	size;

// 	size = 0;
// 	if (option == 1)
// 	{
// 		while (s[i] != ' ' && s[i])
// 		{
// 			size++;
// 			i++;
// 		}
// 	}
// 	else if (option == 2)
// 	{
// 		while (s[i] != '"' && s[i])
// 		{
// 			size++;
// 			i++;
// 		}
// 	}
// 	return (size);
// }



// int		ft_is_whitespace(char c)
// {
// 	if (c == ' ' || c == '\t' || c == '\0')
// 		return (1);
// 	return (0);
// }

// char	**ft_split(char const *s)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	int		word;
// 	char	**strs;
// 	int		flag;

// 	flag = 0;
// 	i = 0;
// 	j = -1;
// 	word = ft_old_nbword(s);
// 	strs = (char **)malloc((word + 1) * sizeof(char *));
// 	if (!strs)
// 		return (NULL);
// 	while (++j < word)
// 	{
// 		while (s[i] == ' ' && flag == 0)
// 			i++;
// 		size = ft_lword(s, i, 1);
// 		strs[j] = ft_substr(s, i, size);
// 		if (!strs[j])
// 			return (NULL);
// 		i += size;
// 	}
// 	strs[j] = 0;
// 	return (strs);
// }

// int	has_quote(char *s)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '"')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	int		wdc;
// 	char	*s;
// 	char **tmp;

// 	int i = 0;

// 	while (1)
// 	{
// 		s = readline("TEST$> ");

// 		wdc = ft_old_nbword(s);
// 		tmp = ft_split(s);

// 		printf("hello - %d\n", ft_old_nbword(s));
// 		i = 0;
// 		printf("--- etape 1 ---\n");
// 		while (i < wdc)
// 		{
// 			printf("|%s|", tmp[i]);
// 			printf(" has quote = %d", has_quote(tmp[i]));
// 			printf("\n");
// 			i++;
// 		}
// 		i = 0;
// 		int srt = -1;
// 		int end = -1;
// 		while (i < wdc)
// 		{
// 			if (has_quote(tmp[i]) == 1)
// 			{
// 				if (srt == -1)
// 					srt = i;
// 				else
// 					end = i;
// 			}
// 			i++;
// 		}
// 		tmp[srt] = ft_strjoin(tmp[srt], " ");
// 		tmp[srt] = ft_strjoin(tmp[srt], tmp[end]);
// 		i = 0;

// 		printf("--- etape 2 ---\n");
// 		while (i < wdc)
// 		{
// 			printf("|%s|\n", tmp[i]);
// 			i++;
// 		}
// 		//printf("Number of words: %d\n", ft_count_words(s));
// 		free(s);
// 	}
//     return (0);
// }


// int	chk_quote(char *s) // return 1 if every quotes are closed and 0 if not and no mix
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != 0)
// 	{
// 		if (s[i] == 39)
// 		{
// 			i++;
// 			while (s[i] != 39)
// 			{
// 				if (s[i++] == 0)
// 					return (0); // not closed with '' / can be changed to have an error correct, ex -1
// 			}
// 		}
// 		if (s[i] == '"')
// 		{
// 			i++;
// 			while (s[i] != '"')
// 			{
// 				if (s[i++] == 0)
// 					return (0); // not closed but with "" / can be changed to have an error correct -2
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int	many_dots(char *s, int i)
{
	int j;
	int	flag;

	flag = 0;
	while (s[i])
	{
		if (s[i] == '.')
		{
			i++;
			j++;
			if (j >= 1)
				flag = 1;
		}
		else if (s[i] == '/' && s[i + 1] == '\0' && flag == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	main(void)
{
	char *s;
	int i = 1;

	if (i == 0)
		printf("0\n");
	perror("ok");
	// while (42)
	// {
	// 	s = readline("test string there -> ");
	// 	printf("%d\n", many_dots(s, 0));
	// 	free(s);
	// }
}