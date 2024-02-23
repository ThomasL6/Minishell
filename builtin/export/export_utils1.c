#include "../../include/minishell.h"


int ft_super_countwords(const char *s)
{
    int count = 0;
    int inside_word = 0;

    while (*s)
    {
        if (*s == ' ')
            inside_word = 0;
        else if (inside_word == 0)
        {
            inside_word = 1;
            count++;
        }
        s++;
    }
    return count;
}

const char *ft_skip_spaces(const char *s)
{
    while (*s && *s == ' ')
        s++;
    return s;
}

int ft_get_word_size(const char *s)
{
    int size = 0;
    int insidequotes = 0;

    while (s[size])
    {
        if (s[size] == '\"')
            insidequotes = !insidequotes;
        else if (s[size] == ' ' && !insidequotes)
            break;
        size++;
    }
    return size;
}

char *ft_extract_word(const char *s, int size)
{
    char *word = (char *)malloc((size + 1) * sizeof(char));
    if (!word)
        return NULL;
    for (int i = 0; i < size; i++)
        word[i] = s[i];
    word[size] = '\0';
    return word;
}

char **ft_super_split(char const *s)
{
    int j = 0;
    int word_count = ft_super_countwords(s);
    char **strs = (char **)malloc((word_count + 1) * sizeof(char *));
    if (!strs)
        return NULL;

    while (*s && j < word_count)
    {
        s = ft_skip_spaces(s);
        int word_size = ft_get_word_size(s);
        if (j > 0 && *(s - 1) == '=' && word_size == 0)
            word_size++;
        strs[j] = ft_extract_word(s, word_size);
        if (!strs[j])
        {
            // Gestion d'erreur : libérer la mémoire allouée précédemment
            for (int k = 0; k < j; k++)
                free(strs[k]);
            free(strs);
            return NULL;
        }
        j++;
        s += word_size;
    }
    strs[j] = NULL;
    return strs;
}