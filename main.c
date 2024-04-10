/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <vamologl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:06:26 by vamologl          #+#    #+#             */
/*   Updated: 2024/04/10 11:19:06 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_signal = 0;

void	received_signal(int n)
{
	if (n == SIGTSTP || n == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (n == SIGQUIT)
		printf("\b\b  \b\b");
}

void	triple_free_tab(char ***tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!tab)
		return ;
	while(tab && tab[i])
	{
		j = 0;
		while(tab && tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		if (tab[i + 1] != NULL)
			i++;
	}
}

void	ft_loop(t_base *base)
{
	while (1)
	{
		base->tablen = 0;
		base->return_value_flag = 0;
		base->input = readline(base->user);
		if (base->input == NULL)
		{
			g_signal = 255;
			break ;
		}
		else if (is_empty(base->input) == 0)
		{
			free(base->input);
			continue ;
		}
		else if (chk_quote(base->input) != 1)
		{
			printf("Error - Quotes are not closed\n"); // should redo the phrasing
			free(base->input);
			continue ;
		}
		else
		{
			base->loop++;
			add_history(base->input);
			parser(base);
			free(base->input);
			free_tab(base->tableau[0]);
		}
	}
	ft_exit(base, 2);
}

void	init_base(t_base *base, char **env)
{
	base->tableau = malloc(sizeof(char ***) * 1);
	base->tableau[0] = NULL;
	base->input = NULL;
	base->user = NULL;
	base->cur_pwd = NULL;
	base->env_old = env;
	base->output_file = NULL;
	base->env = NULL;
	base->command = NULL;
	base->terminal_in = dup(1);
	base->terminal_out = dup(0);
	base->fd_in = dup(1);
	base->fd_out = dup(0);
	base->env_path = NULL;
	base->flag_redir = 0;
	base->return_value = 0;
	base->return_value_flag = 0;
	base->loop = 0;
	base->tablen = 0;
}

int	main(int ac, char **av, char **env)
{
	t_base *base;

	(void)ac;
	(void)av;

	signal(SIGINT, &received_signal);
	signal(SIGTSTP, &received_signal);
	signal(SIGQUIT, &received_signal);
	//signal(SIGSEGV, &received_signal); // remove this

	base = malloc(sizeof(t_base));
	init_base(base, env);
	// ft_putstr_fd("-- opened Minishell --\n", base->ft_custom_exit);
	initial_chain(&base->env, env); // clone env
	init_user(base);
	
	ft_loop(base); // loop
	rl_clear_history(); // clear historic
	ft_exit(base, 0); // exit
	return (0);
}


