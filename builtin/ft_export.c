#include "../include/minishell.h"

void add_more_link(t_env **chain, char *str)
{
    t_env *link;
    t_env *last_link;
    int flag; 
    t_env *existing_link;
	
	existing_link = *chain;
	flag = 0;
    link = malloc(sizeof(*link));
    if (NULL == link)
        return;
    link->next = NULL;
    char *equal_ptr = strchr(str, '=');
    if (equal_ptr != NULL)
        flag = 1;
    if (flag == 1)
    {
        link->name = ft_strjoin(ft_dup_name(str), "=");
        link->value = ft_dup_value(str);
    }
    else
    {
        link->name = ft_strdup(str);
        link->value = NULL;
    }
    while (existing_link)
    {
        if (strncmp(existing_link->name, link->name, (ft_strlen(existing_link->name))) == 0)
        {
            existing_link->name = ft_strjoin(ft_dup_name(str), "=");
            existing_link->value = ft_dup_value(str);
            free(link->name);
            free(link->value);
            free(link);
            return;
        }
        existing_link = existing_link->next;
    }
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




void	print_list_env_export(t_env *env_struct)
{
	if (!env_struct)
	{
		printf("error - print list not there");
		return ;
	}
	while (env_struct)
	{
		if (env_struct->name)
			printf("declare -x ");
		if (env_struct->name)
			printf("%s", env_struct->name);
		if (env_struct->value)
		{
			if (env_struct->value[0] == '\"' && env_struct->value[ft_strlen(env_struct->value) - 1] == '\"')
				printf("%s", env_struct->value);
			else
				printf("\"%s\"", env_struct->value);
		}
		if (!env_struct->name && !env_struct->value) 
			printf("name and value not set\n");
		else
			printf("\n");
		env_struct = env_struct->next;
    }
}

int	ft_export(t_base *base)
{
	int i;

	i = 1;
	if (!base->tableau)
		return (0);
	if (base->tableau[1] == NULL)
	{
		print_list_env_export(base->env);
		return (1);
	}
	while (base->tableau[i])
	{
		add_more_link(&base->env, base->tableau[i]);
		i++;
	}
	return (1);
}