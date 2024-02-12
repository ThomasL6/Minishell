
#include "../include/minishell.h"

void    add_link(t_env **chain, char *env)
{
    t_env   *link;
    t_env   *last_link;

    link = malloc(sizeof * link);
    if (NULL == link)
        return ;
    link->next = NULL;
    link->name = ft_dup_name(env);
    link->value = ft_dup_value(env);
	if (ft_strcmp(link->name, "SHLVL") == 0)
    	link->value = ft_shlvl_var(link->value);
    if (*chain == NULL)
    {
        *chain = link;
        link->previous = NULL;
    }
    else
    {
        last_link = find_last(*chain);
        last_link->next = link;
        link->previous = last_link;
    }
}

void    initial_chain(t_env **chain, char **env)
{
    int i;

    i = 0;
    if (!env)
    {
        printf("Env t exist\n");
        return;
    }
    while (env[i])
    {
        if (!chain)
            return ;
        add_link(chain, env[i]);
        i++;
    }
    printf("chained initialized\n");
}

void	print_list_env(t_env *env_struct)
{
	if (!env_struct)
	{
		printf("error - print list not there");
		return ;
	}
	while (env_struct)
	{
		if (env_struct->name && env_struct->value)
			printf("%s=%s\n", env_struct->name, env_struct->value);
		else
			printf("name and value not set");
		env_struct = env_struct->next;
	}
}

