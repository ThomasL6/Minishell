#include "../include/minishell.h"


int	ft_is_that_char(const char *s, int c) // return len before the char
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (ft_strlen(s));
}

int there_is_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	link_already_exist(t_env *chain, char *env)
{
	if (!chain)
	{
		printf("Error - link already exist- Chain isn't avilable\n");
		return (0);
	}
	while (chain)
	{
		if (ft_strncmp(chain->name, env, ft_is_that_char(env, '=')) == 0)
		{
			printf("Error - variable already found\n");
			return (1);
		}
		chain = chain->next;
    }
	printf("Error - variable not found\n");
	return (0);
}

t_env	*get_link(t_env *chain, char *env)
{
	t_env	*list;

	if (!chain)
	{
		printf("Error - get link - Chain not found\n");
		return (NULL);
	}
	list = chain;
	while (list->next)
	{
		if (ft_strncmp(list->name, env, ft_is_that_char(env, '=') - 1) == 0)
		{
			printf("Error - string is found\n");
		//	printf("list name found is = %s\n", list->name);
			break ;
		}
		else
		//	printf("list name = %s\n", list->name);
		list = list->next;
	}
	return (list);
}


void update_more_link(t_env *chain, char *env)
{
	t_env	*link;
	if (!chain || !env)
		printf("Error - arg not avilable\n");
	printf("Update link\n");
	link = get_link(chain, env);
	if (!link)
	{
		printf("Error - link not found\n");
		return ;
	}
	printf("%s\n", link->name);
	link->name = ft_strndup(env, ft_is_that_char(env, '='));
	if (there_is_equal(env) == 1)
		link->value = ft_dup_value(env);
	else
		link->value = NULL;
}


void add_more_link(t_env **chain, char *env) 
{
    t_env   *link;
    t_env   *last_link;
    char    *equal_ptr;

    link = malloc(sizeof(*link)); if (!link) return; link->next = NULL;

    equal_ptr = strchr(env, '=');
    if (equal_ptr != NULL) 
    {
        link->name = ft_strndup(env, equal_ptr - env);
        
        char *value_start = equal_ptr + 1;
        if (*value_start == '"') 
        {
            char *end_quote = strchr(value_start + 1, '"');
            if (end_quote != NULL) 
            {
                link->value = ft_strndup(value_start, end_quote - value_start + 1);
            } 
            else 
            {
                link->value = ft_strdup(value_start);
            }
        } 
        else 
        {
            link->value = ft_strdup(value_start);
        }
    } 
    else 
    {
        link->name = ft_strdup(env);
        link->value = NULL;
    }

    if (*chain == NULL) 
    { 
        *chain = link; 
        link->previous = NULL; 
    } 
    else 
    {
        last_link = *chain;
        while (last_link->next != NULL) 
        { 
            last_link = last_link->next; 
        }
        last_link->next = link;
        link->previous = last_link;
    }
}



void print_list_env_export(t_env *env_struct) {
    if (!env_struct) {
        printf("error - print list not there");
        return;
    }
    while (env_struct) {
        if (env_struct->name)
            printf("declare -x ");
        if (env_struct->name)
            printf("%s", env_struct->name);
        if (env_struct->value) {
            // if (env_struct->value[0] == '\"' && env_struct->value[ft_strlen(env_struct->value) - 1] == '\"')
            //  printf("%s", env_struct->value);
            // else
            printf("\"%s\"", env_struct->value);
        }
        if (!env_struct->name && !env_struct->value)
            printf("name and value not set\n");
        else
            printf("\n");
        env_struct = env_struct->next;
    }
}

int	ft_export_old(t_base *base)
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
		if (link_already_exist(base->env, base->tableau[i]) == 1)
			update_more_link(base->env, base->tableau[i]);
		else
			add_more_link(&base->env, base->tableau[i]);
		i++;
	}
	return (1);
}

int	goto_old_env_var(t_base *base, char *var_name)
{
	int i;

	i = 0;
	while (base->env_old[i])
	{
		if (ft_strncmp(var_name, base->env_old[i], \
			ft_is_that_char(var_name, '=')) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	goto_end_old_env_var(t_base *base)
{
	int i;

	i = 0;
	while (base->env_old[i])
	{
		if (base->env_old[i] == NULL)
			return (i);
		i++;
	}
	return (i);
}


int ft_export(t_base *base) {
    int i;

    i = 1;
    if (!base->tableau)
        return (0);
    if (base->tableau[1] == NULL) {
        print_list_env_export(base->env);
        return (2);
    }
    while (base->tableau[i]) {
        if (there_is_equal(base->tableau[i])) {
            if (!(link_already_exist(base->env, base->tableau[i]) == 1)) {
                add_more_link(&base->env, base->tableau[i]);
            } else {
                update_more_link(base->env, base->tableau[i]);
            }
        } else {
            // Concatenate value to existing variable's value
            t_env *link = get_link(base->env, base->tableau[i]);
            if (link) {
                char *old_value = link->value;
                char *new_value = ft_strdup(base->tableau[i]);
                char *concatenated_value = ft_strjoin(old_value, new_value);
                free(link->value);
                link->value = concatenated_value;
                free(new_value);
            } else {
                add_more_link(&base->env, base->tableau[i]);
            }
        }
        i++;
    }
    return (1);
}
