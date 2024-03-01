#include "../../include/minishell.h"


int	link_already_exist(t_env *chain, char *env)
{
	if (!chain)
	{
		//printf("Error - link already exist- Chain isn't avilable\n");
		return (0);
	}
	while (chain)
	{
		if (ft_strncmp(chain->name, env, ft_is_that_char(env, '=') - 1) == 0)
		{
			//printf("Error - variable already found\n");
			return (1);
		}
		chain = chain->next;
    }
	//printf("Error - variable not found\n");
	return (0);
}

void print_list_env_export(t_base *base)
{
	int i;
	char **env;

	env = base->env_old;

	i = ft_tablen(base->env_old);
	sorted(i, env, base);
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

void	add_env_old(char **env_old, char *str)
{
	int i = 0;
	while (env_old[i])
	{
		if (env_old[i][0] == '\0')
		{
			env_old[i] = ft_strdup(str);
			return ;
		}
		i++;
	}
	env_old[i] = ft_strdup(str);
	env_old[i + 1] = NULL;

}

void	update_env_old(t_base *base, char *new_value)
{
	remove_old_env(base, new_value);
	add_env_old(base->env_old, new_value);
}



int	ft_export(t_base *base)
{
	char	**ret;
	int i;

	i = 1;

	if (!base->input)
		return (0);
	ret = ft_super_split(base->input);
	if (ret[1] == NULL && ft_strcmp(ret[0], "export") == 0)
	{
		print_list_env_export(base);
		return (1);
	}
	while (ret[i])
	{
		if (check_if_storable(ret[i]) == 0)
		{
			ft_putstr_fd("Error export - `", base->fd_out);
			ft_putstr_fd("ret[i]", base->fd_out);
			ft_putstr_fd("\': not a valid identifier\n", base->fd_out);
		}
		else
		{
			if (link_already_exist(base->env, ret[i]) == 0)
			{
				add_more_link(&base->env, ret[i]);
				add_env_old(base->env_old, ret[i]);
			}
			else
			{
				update_more_link(base->env, ret[i], base);
				update_env_old(base, ret[i]);
			}

		}
		i++;
	}
	return (1);
}
