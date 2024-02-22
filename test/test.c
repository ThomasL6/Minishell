/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:24:50 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/19 11:24:54 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "include/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h> // For debugging

// Function to count words while considering quotes
int countwords(char const *str) {
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

// Function to create a substring
char *ft_substr(char const *s, unsigned int start, size_t len) {
    size_t i;
    char *str;

    if (!s)
        return NULL;
    if (ft_strlen(s) < start)
        return ft_strdup("");
    len = (ft_strlen(s + start) < len) ? ft_strlen(s + start) : len;
    str = (char *)malloc((len + 1) * sizeof(char));
    if (!str)
        return NULL;
    for (i = 0; i < len; i++)
        str[i] = s[start + i];
    str[i] = '\0';
    return str;
}

// Function to split string while considering quotes
char **ft_special_split(char const *s) {
    int j = 0;
    int word = countwords(s);
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

// Test program
int main() {
    char input[] = "this is= \"a test\" string with=quotes";
    char **result = ft_special_split(input);
    if (result) {
        for (int i = 0; result[i]; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }
    return 0;
}

