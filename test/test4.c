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

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
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

char	*is_it_a_name_that_i_can_use(char *s)
{
	char *tmp = "gregoire";

	if (!s)
		return (NULL);
	free(s);
	return (tmp);	
}

char	*gest_dollar(char *s)
{
	int		i;
	int		j;
	int		k;
	char 	*tmp;
	char 	*tmp2;

	k = 0;
	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(s) + 1);
	if(!tmp)
		return(NULL);
	tmp2 = malloc(sizeof(char) * 256);
	if(!tmp2)
		return(NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			while (s[i] && s[i] != ' ' && s[i] != '\t')
			{
				tmp2[k] = s[i];
				i++;
				k++;
			}
			tmp2[k] = '\0';
			tmp2 = is_it_a_name_that_i_can_use(tmp2);
			tmp = ft_strjoin(tmp, tmp2);
			j = ft_strlen(tmp);
		}
		else
		{
			tmp[j] = s[i];
			i++;
			j++;
		}
	}
	printf("tmp2 = [%s]\n", tmp2);
	tmp[j] = '\0';
	free(s);
	return (tmp);
}


int main(void)
{
	int i;
	char *s;

	s = NULL;
	while(1)
	{
		i = 0;
		s = readline(" Test file ~$ ");
		if (s == NULL)
			break;
		add_history(s);
		printf("ret gest dollar = [%s]\n", s);

		s = gest_dollar(s);
		char *tmp = ft_strndup(s, ft_strlen(s));
		printf("ret gest dollar = [%s]\n", tmp);
		free(s);
		free(tmp);
	}
}