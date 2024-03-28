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

#include "../include/minishell.h"

void	get_input_tab_spe(t_base *base, char **command)
{
	int	j;

	j = 0;
	command = ft_super_split(base->input);
	while (command[j])
	{
		base->tableau[0][j] = ft_strndup(command[j], nb_char(command[j]));
		j++;
	}
}

void	tab_printf(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
	{
		dprintf(1, "tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

void	gest_pipe_and_redir2(t_base *base, char ***command, int i)
{
	base->input = correct_input_for_parser(base->input);
	if (find_pipe(base->input) == -1)
	{
		get_input_tab_spe(base, command[i]);
		tab_printf(command[i]);
	}
	get_file_inpout(base, command[i], i);
	command[i] = get_exec(command[i]);
	get_command(command, i, base);
	return ;
}

void	fd_change(t_base *base)
{
	if (base->tableau[0][1] == NULL)
	{
		base->fd_out = 1;
		return ;
	}
	else if (base->tableau[0][2] != NULL)
	{
		dprintf(base->fd_out, "Error - too many arguments\n");
		// dprintf(base->ft_custom_exit, "Error - too many arguments\n");
		return ;
	}
	else
		base->fd_out = open(base->tableau[0][1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	return ;
}

void	get_file_inpout(t_base *base, char **av, int i)
{
	if (is_there_redir(av))
	{
		if (only_one_redir(av) == 1)
		{
			if (is_there_redir(av) == 4)
				ft_double_lredir(base, i);
			else if(is_there_redir(av) == 1)
				ft_basic_redir(av, base, i);
			else if (is_there_redir(av) == 2)
				ft_double_redir(av, base, i);
			else if (is_there_redir(av) == 3)
				if (ft_left_redir(av, base, i) != 0)
					return ;
		}
		else
			multi_redir(av, base, i);
	}
}

int	hm_ultra_tab(char ***tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	get_command(char ***tableau, int j, t_base *base)
{
	if (no_command(tableau[j]) == 0)
	{
		if (ft_strcmp("", tableau[j][0]) == 0)
			return ;
		else if (ft_strcmp("env", tableau[j][0]) == 0)
			own_env(base, j);
		else if (ft_strcmp("echo", tableau[j][0]) == 0)
			own_echo(base, j);
		else if (ft_strcmp("pwd", tableau[j][0]) == 0)
			get_pwd(base);
		else if (ft_strcmp("cd", tableau[j][0]) == 0)
			own_cd(base->input, base);
		else if (ft_strcmp("export", tableau[j][0]) == 0)
			ft_export(base);
		else if (ft_strcmp("unset", tableau[j][0]) == 0)
			ft_unset(base);
		else if (ft_strcmp("exit", tableau[j][0]) == 0)
			ft_exit(base, j);
		else if (!ft_exec_prog(tableau[j], base))
		{
			ft_putstr_fd(base->tableau[j][0], base->fd_out);
			ft_putstr_fd(": command not found\n", base->fd_out);
			base->return_value = 127;
		}
	}
}

void	print_tab(char ***tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			dprintf(1, "tab[%d][%d] = %s\n", i, j, tab[i][j]);
			j++;
		}
		i++;
	}
}

void	parser(t_base *base)
{
	if (base->return_value_flag == 1)
	{
		write(base->fd_out, ft_itoa(base->return_value), ft_strlen(ft_itoa(base->return_value)));
		write(base->fd_out, "\n", 2);
	}
	dup2(base->terminal_in, base->fd_in);
	dup2(base->terminal_out, base->fd_out);
	base->input = init_input(base->input);//
	if (find_pipe(base->input) == -1)
		get_input_tab(base, 0);
	else
	{
		base->tableau = pre_build_tab(base, base->input);
		print_tab(base->tableau);
		// gest_dollar_multipipe(base);
		execute_pipeline(base->tableau, hm_ultra_tab(base->tableau), base);
		return ;
	}
	get_file_inpout(base, base->tableau[0], 0); // set in/out
	base->tableau[0] = get_exec(base->tableau[0]); // get exec
	get_command(base->tableau, 0, base);
	ft_bzero(base->input, ft_strlen(base->input));
	dup2(base->terminal_in, base->fd_out);
	dup2(base->terminal_out, base->fd_in);
}

