/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vamologl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:06:26 by vamologl          #+#    #+#             */
/*   Updated: 2024/01/23 11:06:28 by vamologl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"



void	received_signal(int n)
{
	if (n == SIGTSTP)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (n == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (n == SIGSEGV) // mem crash should not be there
	{
		printf("SIGSEGV -> Fuck you\n");
		exit(-2147483647);
	}
}

int	ft_parser(char *s)
{
	if (chk_quote(s) != 1)
	{
		printf("Error - Quotes are not closed,"); // should redo the phrasing
		printf(" missing either \' of \" \n");
		return (-1);
	}
	if (chk_pipe_start(s) == 1)
	{
		printf("Error - First character in string should not"); // should redo the phrasing
		printf(" be a |\n");
		return (-2);
	}
	else
	{
		printf("Error - else condition does not exist\n");
		return (0);
	}
	return (1);
}


void    gest_intp(t_base *base)
{
	add_history(base->input);
	if (chk_directory(base) == 0)
	{
		free(base->input);
	}
	parser(base);
	// while() // -> parcours le tableau jusque end
	// {
	// 	while() // -> parcours le tableau jusque "|"
	// 	{
	// 		if (is_input())
	// 			input();
	// 		else
	// 		{
	// 			exec()
	// 		}
	// 		// pour les deux pensez aux chevrons  
	// 	}
	// }
}

void	ft_loop(t_base *base)
{
	while (1)
	{
		base->input = readline(base->user);
		if (base->input == NULL)
			ft_exit(&base->env);
		else if (is_empty(base->input) == 0)
			continue;
		gest_intp(base); // go to error in string
	}
}



int	main(int ac, char **av, char **env)
{
	t_base *base;

	(void)ac;
	(void)av;

	//base = NULL;
	signal(SIGINT, &received_signal);
	signal(SIGTSTP, &received_signal);
	signal(SIGQUIT, &received_signal);
	//signal(SIGSEGV, &received_signal); // remove this


	base = malloc(sizeof(t_base));
	base->env_old = env;
	initial_chain(&base->env, env); // clone env
	init_user(base);
	
	ft_loop(base); // loop
	rl_clear_history(); // clear historic

	return (0);
}
