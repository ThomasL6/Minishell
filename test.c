// #include "include/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char	*rm_dollar(const char *s)
{
	size_t	len;
	int		i;
	char	*dst;

	len = strlen((char *)s);
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

int main(int c, char **s)
{
	(void)c;
	if (!s[1])
	{
		printf("error - no input\n");
		return (-1);
	}
	printf("%s\n", rm_dollar(s[1]));
}