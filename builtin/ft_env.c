#include "../include/minishell.h"

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