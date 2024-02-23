#include "include/minishell.h"

int check_if_storable(char *s)
{
	int i;
	int j;

	i = 0;
	if (!s[0])
		return (2);
	else if (s[0] == '=' && s[0])
		return (0);
	else if (s[0] >= '0' && s[0] <= '9' && s[0])
		return (0);
	else if (find_that_char(s, '=') == 1)
	{
		j = ft_is_that_char(s, '=');
		if ((int)ft_strlen(s) == j)
			return (2);
		while (i < j)
		{
			if (ft_isalnum(s[i]) == 0)
				return (0);
			else
				i++;
		}
	}
	return (1);
}
