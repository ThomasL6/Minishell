#include "../include/minishell.h"

void remove_link(t_env **chain, char *var_name, t_base *base)
{
    t_env *link;
	int i = 0;

	link = *chain;
    while (link != NULL)
    {
        if (strncmp(link->name, var_name, ft_is_that_char(var_name, '=')) == 0)
        {
            if (link->previous != NULL)
                link->previous->next = link->next;
            else
                *chain = link->next;

            if (link->next != NULL)
                link->next->previous = link->previous;

            free(link->name);
            free(link->value);
            free(link);
			while (base->env_old[i])
			{
				if (base->env_old[i] != NULL && var_name != NULL)
				{
				    size_t index = ft_is_that_char(var_name, '=');
				    if (index < strlen(var_name) && index < strlen(base->env_old[i]))
				    {
				        if (ft_strncmp(var_name, base->env_old[i], index) == 0)
				        {
							ft_bzero(base->env_old[i], \
							ft_strlen(base->env_old[i] + 1));
							base->env_old[i] = NULL;
				        }
					}
				}
				i++;
       		}
            return;
    	}
        link = link->next;
	}
}

void ft_unset(t_base *base)
{
	int i;
	i = 1;

	printf("%s\n", base->input);
	while (base->tableau[i])
	{
		remove_link(&base->env, base->tableau[i], base);
		i++;
	}
}
