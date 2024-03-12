/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:49:03 by vamologl          #+#    #+#             */
/*   Updated: 2024/03/07 11:49:05 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	only_one_type_redir(char **tab) // check if there is only one type of redirection
{
	int	i;
	int	tmp_redir;

	i = 0;
	tmp_redir = -1;
	while (tab[i] && tmp_redir == -1) // get the first redirec
	{
		if (ft_find_redirection(tab[i]) == 1)
			tmp_redir = 1; // >
		else if (ft_find_redirection(tab[i]) == 2)
			tmp_redir = 2; // >>
		else if (ft_find_redirection(tab[i]) == 3)
			tmp_redir = 3; // <
		i++;
	}
	while (tab[i]) // check if every redir is the same as the first one (in t_redir)
	{
		if (ft_find_redirection(tab[i]) != 0 &&
			ft_find_redirection(tab[i]) != tmp_redir)
			return (0); // 0 bc there is more than one type of redir
		i++;
	}
	return (1); // 1 bc everythings is the same
}


// get the | ls | inside | > michel ls >> file < greg |
char    **get_exec(char **tab)
{
	int i;
	int j;
    int k;
    char **ret;

	if (!tab)
		return (NULL);
    i = 0;
	while (tab[i])
	{
		if (ft_find_redirection(tab[i]) != 0 && tab[i])
			i += 2;
		else
			break;
	}
	j = i;
	while (ft_find_redirection(tab[j]) == 0 && tab[j])
		j++;
    k = 0;
    ret = (char **)malloc(sizeof(char *) * (j - i + 1));
	while (i < j)
	{
        ret[k] = ft_strdup(tab[i]);
		i++;
        k++;
	}
    ret[k] = NULL;
    return (ret);
}

void	set_output(char **str, t_base *base) // change the output
{
	int i = 0;
	int j = 0;
	int tmp;
	dprintf(base->ft_custom_exit, "in set_output\n"); //debug

	while (str[i])
	{
		dprintf(base->ft_custom_exit, "loop output\n");	//debug
		if (ft_find_redirection(str[i]) == 2 || ft_find_redirection(str[i]) == 1) // if <<
		{
			tmp = open(str[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644); 
			dup2(tmp, base->fd_out);
			dprintf(base->ft_custom_exit, "changed output, %d\n", tmp); //debug
			j++;
		}
		if (ft_find_redirection(str[i]) == 2 || ft_find_redirection(str[i]) == 1) // if < 
		{
			tmp = open(str[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(tmp, base->fd_out);
			dprintf(base->ft_custom_exit, "changed output, %d\n", tmp); //debug
			j++;
		}
		i++;
	}
}

void	set_input(char **str, t_base *base) // change the input
{
	int i = 0;
	int j = 0;
	int tmp;
	dprintf(base->ft_custom_exit, "in set_input\n");// Debug

	while (str[i])
	{
		dprintf(base->ft_custom_exit, "loop input\n");	// Debug
		if (ft_find_redirection(str[i]) == 3) // if < 
		{
			tmp = open(str[i + 1], O_RDONLY, 0644);
			dup2(tmp, base->fd_in);
			dprintf(base->ft_custom_exit, "changed input, %d\n", tmp); // Debug
			j++;
		}
		i++;
	}
}


// gest multi redirec
void	multi_redir(char **str, t_base *base)
{
	int i = 0;

	dprintf(base->ft_custom_exit, "in multiredir\n"); // Debug
	if (only_one_type_redir(str))
	{
		dprintf(base->ft_custom_exit, "if multiredir\n"); // Debug
		while (str[i])
		{
			if (ft_find_redirection(str[i]) == 1 || ft_find_redirection(str[i]) == 2) // > or >>
			{
				set_output(str, base); 	// set output
				base->fd_in = 0;		// reset in to terminal input, maybe broken
				break ;
			}
			else if (ft_find_redirection(str[i]) == 3) // only <, << not supported
			{
				set_input(str, base);	// set input
				base->fd_out = 1;		// reset out to teminal output, maybe broken
				break ;
			}
			else if (ft_find_redirection(str[i]) == 4) // only <, << not supported
			{
				ft_double_lredir(base);	// set input
				base->fd_out = 1;
				base->fd_in = 0;		// reset out to teminal output, maybe broken
				break ;
			}
			i++;
		}
	}
	else
	{
		dprintf(base->ft_custom_exit, "else multiredir\n"); // Debug
		ft_double_lredir(base);
		set_input(str, base);	// set input
		set_output(str, base);	// set output
		
	}
}
