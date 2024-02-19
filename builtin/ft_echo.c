/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:09:18 by vamologl          #+#    #+#             */
/*   Updated: 2024/02/02 14:09:19 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_strcmp_spe(char *string, char *compared, int srt, int end)
{
    int i = 0;
    while (string[srt] == compared[i] && string[srt] != '\0' &&
           compared[i] != '\0' && srt < end)
    {
        i++;
        srt++;
    }
    return (string[srt] - compared[i]);
}

void ft_print_env(t_env *chain, char *name, int srt, int end)
{
    if (NULL == chain)
        return;
    while (chain)
    {
        if (ft_strcmp_spe(name, chain->name, srt, end) == 0)
        {
            printf("%s", chain->value);
            return;
        }
        chain = chain->next;
    }
}

int is_char_or_num(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        return (1);
    else
        return (0);
}


int is_env(char *s, t_base *base, int i)
{
    int srt = i;
    int end;
    while (s[i])
    {
        i++;
        if ((s[i + 1] == ' ' || s[i + 1] == '\'' || s[i + 1] == '\"'))
            break;
		else if (!is_char_or_num(s[i + 1]))
			break ;
    }
    end = i;
    ft_print_env(base->env, s, srt, end);
    return (i - srt + 1); // Retourne le nombre de caractères traités
}

void echo_verif_dollar(t_base *base, int i)
{
    int j;

	j = 0;
    while (base->tableau[i][j])
    {
        if (base->tableau[i][j] == '$' && base->tableau[i][0] != '\'')
        {
            j++;
            j += is_env(base->tableau[i], base, j);
        }
        else
        {
            if (base->tableau[i][j] != '\'' && base->tableau[i][j] != '\"')
                printf("%c", base->tableau[i][j]);
            j++;
        }
    }
    if (base->tableau[i + 1])
        printf(" ");
}


void own_echo(t_base *base)
{
    int flag;
    int i;
    
    flag = 0;
    i = 1;
    if (base->tableau[0] && !base->tableau[1])
    {
        printf("\n");
        return;
    }
    else if (base->tableau[1])
    {
        while (base->tableau[i] && base->tableau[i][0] == '-')
        {
            if (strcmp(base->tableau[i], "-n") == 0)
            {
                flag = 1;
                i++;
            }
            else
                break;
        }
        while (base->tableau[i])
        {
            // printf("is in the if 2\n");
            echo_verif_dollar(base, i);
            i++;
        }
        if (flag == 0)
            printf("\n");
    }
}

