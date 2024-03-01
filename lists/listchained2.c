
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

void    initial_chain(t_env **chain, char **env, t_base *base)
{
    int i;

    i = 0;
    if (!env)
    {
        ft_putstr_fd("Env t exist\n", base->fd_out);
        // printf("Env t exist\n");
        return;
    }
    while (env[i])
    {
        if (!chain)
            return ;
        add_link(chain, env[i]);
        i++;
    }
    // printf("chained initialized\n"); // to remove
    ft_putstr_fd("chained initialized\n", base->fd_out);
}

void	print_list_env(t_env *env_struct, t_base *base)
{
	if (!env_struct)
		return ;
	while (env_struct)
	{
        if (env_struct->name[ft_strlen(env_struct->name) - 1] == '=')
        {

		    if (env_struct->name && env_struct->value)
            {
                ft_putstr_fd(env_struct->name, base->fd_out);
                //ft_putchar_fd('=', base->fd_out);
                ft_putstr_fd(env_struct->value, base->fd_out);
                ft_putstr_fd("\n", base->fd_out);
            }
            else
                ft_putstr_fd("name and value not set\n", base->fd_out);    
            env_struct = env_struct->next;
        }
        else
            env_struct = env_struct->next;
	}
}
