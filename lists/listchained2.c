
#include "../include/minishell.h"


void    add_link(t_env **chain, char *env)
{
    t_env   *link;
    t_env   *last_link;

    link = malloc(sizeof * link);
    if (NULL == link)
        return ;
    link->next = NULL;
    link->name = ft_strjoin(ft_dup_name(env), "=");
    link->value = ft_dup_value(env);
	if (ft_strcmp(link->name, "SHLVL=") == 0)
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
		return ;
	while (env_struct)
	{
        if (env_struct->name[ft_strlen(env_struct->name) - 1] == '=')
        {

		    if (env_struct->name && env_struct->value)
            {
                ft_putstr_fd(env_struct->name, 0);
                ft_putstr_fd(env_struct->value, 0);
                ft_putstr_fd("\n", 0);
            }
            else
                ft_putstr_fd("name and value not set\n", 0);    
            env_struct = env_struct->next;
        }
        else
            env_struct = env_struct->next;
	}
}
