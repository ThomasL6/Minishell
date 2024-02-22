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
    char *value_start;
    char *end_quote;

    link = malloc(sizeof(*link));
	if (!link) return; 
	{
			link->next = NULL;
			equal_ptr = strchr(env, '=');
	}
    if (equal_ptr != NULL) 
    {
        link->name = ft_strndup(env, equal_ptr - env);
		value_start = equal_ptr + 1;
        if (*value_start == '"') 
        {
			end_quote = strchr(value_start + 1, '"');
            if (end_quote != NULL) 
                link->value = ft_strndup(value_start, end_quote - value_start + 1);
            else 
                link->value = ft_strdup(value_start);
        } 
        else 
            link->value = ft_strdup(value_start);
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
            last_link = last_link->next; 
        last_link->next = link;
        link->previous = last_link;
    }
}
/*  On commence par allouer de la mémoire pour un nouveau maillon link de type t_env.
    Si l'allocation échoue, la fonction retourne immédiatement.
    On initialise le pointeur next de link à NULL.
    On cherche le caractère '=' dans la chaîne env. Si ce caractère est trouvé, on l'utilise pour diviser la chaîne en deux parties : le nom de la variable et sa valeur.
    On alloue de la mémoire pour le nom de la variable link->name et on y copie la partie de la chaîne env avant le '='.
    Si la valeur de la variable commence par une double quote '"', on cherche la fin de la double quote dans la chaîne. 
	Si elle est trouvée, on alloue de la mémoire pour link->value et on y copie la partie de la chaîne entre les deux double quotes, y compris les quotes.
	Sinon, on copie simplement la partie restante de la chaîne après le '='.
    Si la valeur de la variable ne commence pas par une double quote, on copie simplement la partie restante de la chaîne après le '='.
    Si chain est NULL, cela signifie que la liste chaînée est vide. Dans ce cas, on pointe chain vers le nouveau maillon link et on initialise le pointeur previous de link à NULL.
    Si chain n'est pas NULL, cela signifie que la liste chaînée contient déjà des maillons.
	On parcourt alors la liste jusqu'au dernier maillon, puis on relie le nouveau maillon link à la fin de la liste en mettant à jour les pointeurs next et previous appropriés.*/


void	ft_putstr(char *str)
{
	int i;

	i = 0;
	write(1, "declare -x ", 11);
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}


void print_list_env_export(t_base *base)
{
	int argc = ft_tablen(base->env_old);
	char **argv = base->env_old;

	int		i2;
	int		i1;
	char	*tmp;

	i2 = argc;
	i1 = 1;

	while (++i1 <= argc)
	{
		i2 = 1;
		while (++i2 <= argc - 1)
		{
			if (ft_strcmp(argv[i2], argv[i2 - 1]) < 0)
			{
				tmp = argv[i2];
				argv[i2] = argv[i2 - 1];
				argv[i2 - 1] = tmp;
			}
		}
	}
	i1 = 0;
	while (++i1 < argc)
		ft_putstr(argv[i1]);

}

// Function to count words while considering quotes
int ft_super_countwords(char const *str) {
    int count = 0;
    int insidequotes = 0;

    while (*str) {
        if (*str == '\"')
            insidequotes = !insidequotes;
        else if ((*str == ' ' || *str == '=') && !insidequotes)
            count++;
        str++;
    }
    return count + 1; // Adding 1 for the last word
}

// Function to get the length of a string
size_t ft_strlen(const char *s) {
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}


char **ft_super_split(char const *s)
{
    int j = 0;
    int word = ft_super_countwords(s);
    char **strs = (char **)malloc((word + 1) * sizeof(char *));
    if (!strs)
        return NULL;

    while (*s && j < word) {
        int size = 0;
        int insidequotes = 0;

        while (*s == ' ' || *s == '=')
            s++;

        while (s[size]) {
            if (s[size] == '\"')
                insidequotes = !insidequotes;
            else if ((s[size] == ' ' || s[size] == '=') && !insidequotes)
                break;
            size++;
        }

        if (size == 1 && s[0] == '=' && j > 0) {
            // If the word is just '=', treat it as a separate word
            strs[j++] = ft_substr(s, 0, 1);
        } else if (s - 1 != NULL && *(s - 1) == '=' && j > 0) {
            // If previous character was '=', concatenate it with the current word
            char *temp = ft_substr(strs[j - 1], 0, ft_strlen(strs[j - 1]));
            free(strs[j - 1]);
            strs[j - 1] = (char *)malloc((size + 2) * sizeof(char));
            snprintf(strs[j - 1], size + 2, "%s=", temp);
            free(temp);
            strs[j++] = ft_substr(s, 0, size);
        } else if (j > 0 && size > 0 && s[size - 1] == '=') {
            // If the last character is '=', keep it with the current word
            strs[j++] = ft_substr(s, 0, size);
        } else {
            strs[j++] = ft_substr(s, 0, size);
        }
        s += size;
    }
    strs[j] = NULL;
    return strs;
}


int find_that_char(char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(t_base *base)
{
	char	**ret;
	int i;

	i = 0;

	if (!base->input)
		return (0);

	ret = ft_super_split(base->input);
	while (ret[++i])
		printf("%s\n", ret[i]);
	return (1);
}
