#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

        if (size > 0 && s[size - 1] == '=') {
            // If the last character is '=', keep it with the current word
            strs[j++] = (char *)malloc((size + 1) * sizeof(char));
            snprintf(strs[j - 1], size + 1, "%s", s);
        } else {
            strs[j++] = (char *)malloc((size + 1) * sizeof(char));
            snprintf(strs[j - 1], size + 1, "%s", s);
        }
        s += size;
    }
    strs[j] = NULL;
    return strs;
}

void ft_print_super_split(char **strs)
{
    if (strs == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; strs[i] != NULL; i++) {
        printf("%s\n", strs[i]);
        free(strs[i]);
    }
    free(strs);
}

int main() {
    char *input1 = "Tenebris= fsd";
    char *input2 = "Tenebris=";
    char *input3 = "Tenebris =fsd";
    char *input4 = "Tenebris = fsd";
    char *input5 = "Tenebris";

    printf("Export:\n");
    ft_print_super_split(ft_super_split(input1));
    printf("Export:\n");
    ft_print_super_split(ft_super_split(input2));
    printf("Export:\n");
    ft_print_super_split(ft_super_split(input3));
    printf("Export:\n");
    ft_print_super_split(ft_super_split(input4));
    printf("Export:\n");
    ft_print_super_split(ft_super_split(input5));

    return 0;
}

