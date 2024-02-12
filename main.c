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


	// else if (!ft_strcmp(base->input, "env")) 	// to move elsewhere
	// 	print_list_env(base->env); 				// to move elsewhere
	// else if (!ft_strcmp(base->input, "pwd")) 	// to move elsewhere
	// 	get_pwd(base); 							// to move elsewhere
	// else if (!ft_strncmp(base->input, "cd ", 2)) 	// to move elsewhere
	// 	own_cd(base->input); 
	// else if (!ft_strcmp(base->input, "echo")) 	// to move elsewhere
	// 	own_echo(base); 
	// else if (base->input[0] != '\0' && ft_parser(base->input) == 1 
	// 	&& chk_directory(base) == 1) // 1 is every things is OK
	// {
	// 	if (chk_pipe_end(base->input) == 1)
	// 	{
	// 		printf("pipe end 1\n");
	// 		//do shit here
	// 	}
	// 	else if (chk_pipe_end(base->input) == 0)
	// 		printf("random bullshit goes there\n");
	// 		//only_one_command(base);
	// }
	// else
	// 	message_error(base->input, 3); // 3 does not exist




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
		printf("SIGSEGV\n");
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
		printf("else condition does not exist\n");
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

	base = NULL;
	signal(SIGINT, &received_signal);
	signal(SIGTSTP, &received_signal);
	signal(SIGQUIT, &received_signal);

	base = malloc(sizeof(t_base));
	initial_chain(&base->env, env); // clone env
	init_user(base);
	

	//base->lst->head = NULL; // SEGSEGV is there
	ft_loop(base); // loop
	rl_clear_history(); // clear historic

	return (0);
}
